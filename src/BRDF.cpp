#include "BRDF.hpp"
#include "glm/gtc/matrix_transform.hpp"	// Matrix transformations
#include <algorithm>

const static float EPSILON = 0.0001f;

glm::vec3 BRDF::calculateColor(Scene &scene, Intersection &intersection, int recurse_count, printNode* parent) {
	// Base case
	if (recurse_count < 0) {
		return glm::vec3(0, 0, 0);
	}

	// Easing variable names
	GeoObject::Finish *finish = &intersection.object->finish;

	// Verbose printing
	createParentNode(parent, intersection);

	// Colors
	glm::vec3 local_color 		= calculateLocalColor(scene, intersection, recurse_count, parent);
	glm::vec3 reflection_color = calculateReflectionColor(scene, intersection, recurse_count, parent);
	glm::vec3 refraction_color = calculateRefractionColor(scene, intersection, recurse_count, parent);

	// Contributions
	float fresnel_reflectance = 0.f;
	if (fresnel_flag) {
		fresnel_reflectance = calculateFresnelReflectance(finish->ior, intersection);
	}
	float local_contribution = (1.f - finish->filter) * (1.f - finish->reflection);
	float reflectance_contribution = (1.f - finish->filter) * (finish->reflection) + (finish->filter) * (fresnel_reflectance);
	float transmission_contribution = (finish->filter) * (1 - fresnel_reflectance);

	glm::vec3 out_color =  local_color * local_contribution +
								  reflection_color * reflectance_contribution +
								  refraction_color * transmission_contribution;

	updateParentNode(parent, local_contribution, reflectance_contribution, transmission_contribution, out_color);

	return out_color;
}

glm::vec3 BRDF::raytrace(Scene &scene, Ray &incident_ray, int recurse_count, printNode* parent) {
	// Base Case
	if (recurse_count < 0) {
		return glm::vec3(0, 0, 0);
	}

	// If no intersection from camera to object, return black
	Intersection incident_int(scene, incident_ray, spatial_flag);
	if (!incident_int.hit) {
		return glm::vec3(0, 0, 0);
	}

	return calculateColor(scene, incident_int, recurse_count, parent);
}

glm::vec3 BRDF::createSamplePoint(Intersection &intersection, glm::mat4 &matrix) {
	// Generate random UV
	float u = rand() / (float) RAND_MAX;
	float v = rand() / (float) RAND_MAX;
	// Stratified sample
	u += 1/sqrt(gi_samples) * rand() / (float) RAND_MAX;
	v += 1/sqrt(gi_samples) * rand() / (float) RAND_MAX;

	// Create point on hemisphere
	float radial = sqrt(u);
	float theta = 2.f*PI*v;
	glm::vec3 point = glm::vec3(radial*glm::cos(theta), radial*glm::sin(theta), sqrt(1-u));

	// Align hemisphere w/ intersection
	return glm::vec3(matrix * glm::vec4(point, 1.f));
}

glm::vec3 BRDF::calculateLocalColor(Scene &scene, Intersection &intersection, int recurse_count, printNode* parent) {
	// Ambient
	glm::vec3 local_color = intersection.object->finish.color * intersection.object->finish.ambient;
	if (gi_flag) {
		// Global illumination
		int numSamples = gi_samples;

		if (gi_bounces < recurse_count) {
			recurse_count = gi_bounces;
		} 
		else {
			recurse_count--;
		}

		if (gi_bounces - recurse_count > 0) {
			numSamples /= ((gi_bounces - recurse_count) * gi_ratio);
		}

		float angle = glm::acos(glm::dot(glm::vec3(0, 0, 1), intersection.normal));
		glm::vec3 axis = glm::cross(glm::vec3(0, 0, 1), intersection.normal);
		glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), angle, axis);	

		for (int i = 0; i < numSamples; i++) {
			glm::vec3 sample_point = createSamplePoint(intersection, matrix);
			Ray sample_ray(intersection.point + sample_point * EPSILON, sample_point);
			local_color += raytrace(scene, sample_ray, recurse_count, parent);
		}
		local_color /= numSamples;
	}
	if (parent != nullptr) {
		parent->ambient = local_color;
	}

	// Loop through lights
	for (unsigned int i = 0; i < scene.lights.size(); i++) {
		// Calculate ray from object to each light
		Light *light = scene.lights[i];
		glm::vec3 light_dir = glm::normalize(light->position - intersection.point);
		Ray light_ray(intersection.point, light_dir);

		// If no objects are blocking incoming light, BRDF
		Intersection light_int(scene, light_ray, spatial_flag);
		if (!light_int.hit || distance(intersection.point, light->position) < distance(intersection.point, light_int.point)) {
			local_color += render_flag ? CookTorrance(light, intersection) : BlinnPhong(light, intersection, parent);
		}

		// Verbose printing
		if (parent != nullptr) {
			parent->shadow_ray = light_ray;
		}
	}

	return local_color;
}

glm::vec3 BRDF::calculateReflectionColor(Scene &scene, Intersection &intersection, int recurse, printNode* parent) {
	if (!intersection.object->finish.reflection) {
		return glm::vec3(0, 0, 0);
	}

	Ray reflection_ray = createReflectionRay(intersection);
	glm::vec3 reflection_color = raytrace(scene, reflection_ray, recurse-1, createChildNode(parent, 0));

	// Reflection color is scaled by object's material
	reflection_color *= intersection.object->finish.color;

	updateParentNode(parent, reflection_ray, reflection_color, 0);

	return reflection_color;
}

Ray BRDF::createReflectionRay(const Intersection &intersection) {
	const Ray incident_ray = intersection.ray;
	const glm::vec3 incident_point = intersection.point;

	glm::vec3 reflection_dir = normalize(incident_ray.direction - 2 * dot(incident_ray.direction, intersection.normal) *intersection.normal) ;
	glm::vec3 p_z = incident_point + reflection_dir * EPSILON;

	return Ray(p_z, reflection_dir);
}

glm::vec3 BRDF::calculateRefractionColor(Scene &scene, Intersection &intersection, int recurse, printNode* parent) {
	if (!intersection.object->finish.filter) {
		return glm::vec3(0, 0, 0);
	}

	Ray refraction_ray = createRefractionRay(intersection);
	Intersection ref_intersection = Intersection(scene, refraction_ray, spatial_flag);
	// If no intersection
	if (!ref_intersection.hit) {
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 refraction_color = calculateColor(scene, ref_intersection, recurse-1, createChildNode(parent, 1));

	// Beers law
	float dist = glm::distance(ref_intersection.point, intersection.point);
	glm::vec3 absorb = (1.f - intersection.object->finish.color) * (0.15f) * -dist;
	glm::vec3 atten = glm::vec3( exp(absorb.r), exp(absorb.g), exp(absorb.b) );
	refraction_color *= atten;

	updateParentNode(parent, refraction_ray, refraction_color, 1);

	return refraction_color;
}

Ray BRDF::createRefractionRay(const Intersection &intersection) {
	float n1 = 1;
	float n2 = intersection.object->finish.ior;
	glm::vec3 norm = intersection.normal;
	// If we're 'exiting' an object
	if (dot(norm, intersection.ray.direction) > 0) {
		n1 = n2;
		n2 = 1;
		norm = -norm;
	}

	float dDotN = dot(intersection.ray.direction, norm);
	float rat = n1/n2;
	float root = 1-(rat*rat)*(1-dDotN*dDotN);

	glm::vec3 refraction_dir = normalize(rat*(intersection.ray.direction-dDotN*norm)-norm*(float)sqrt(root));
	glm::vec3 p_z = intersection.point + refraction_dir * EPSILON;
	return Ray(p_z, refraction_dir);
}

glm::vec3 BRDF::BlinnPhong(Light *light, Intersection &object_in, printNode* p) {
	// Initialize local vars
	GeoObject::Finish *finish = &object_in.object->finish;
	glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
	glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
	float NdotL = std::max(0.f, dot(object_in.normal, light_dir));
	float HdotN = std::max(0.f, dot(half, object_in.normal));

	// Diffuse
	glm::vec3 diffuse = glm::vec3(0, 0, 0);
	if (NdotL && finish->diffuse) {
		diffuse = finish->diffuse * finish->color * NdotL * light->color;
		if (p != nullptr) {
			p->diffuse += diffuse;
		}
	}

	// Specular
	glm::vec3 specular = glm::vec3(0, 0, 0);;
	if (HdotN && finish->specular) {
		float r_squared = finish->roughness*finish->roughness;
		specular = finish->specular * finish->color  * (float) pow(HdotN, 2/r_squared - 2) * light->color;
		if (p != nullptr) {
			p->specular += specular;
		}
	}

	return diffuse + specular;
}

glm::vec3 BRDF::CookTorrance(Light *light, Intersection &object_in) {
	// Initialize local vars
	GeoObject::Finish *finish = &object_in.object->finish;
	glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
	glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
	float NdotL = std::max(0.f, dot(object_in.normal, light_dir));
	float HdotN = std::max(0.f, dot(half, object_in.normal));
	float NdotV = std::max(0.f, dot(object_in.normal, -object_in.ray.direction));
	float VdotH = std::max(0.f, dot(-object_in.ray.direction, half));

	if (NdotL == 0.f) {
		return glm::vec3(0, 0, 0);
	}

	// Diffuse
	glm::vec3 diffuse = finish->color * (1 - finish->metallic);

	// Specular
	// D - Blinn
	float D = 0.f;
	if (HdotN > 0.f && finish->roughness > 0.f) {
		float r_squared = finish->roughness*finish->roughness;
		D = pow(HdotN, 2/(r_squared*r_squared) - 2)/(PI * r_squared*r_squared);
	}

	// G
	float G = 1.f;
	G = std::min(G, 2.f*HdotN*NdotV/VdotH);
	G = std::min(G, 2.f*HdotN*NdotL/VdotH);

	// F
	float F = fresnel(finish->ior, half, -object_in.ray.direction);

	glm::vec3 specular = finish->color * finish->metallic;
	specular *= (D*G*F) / (4.f*NdotL*NdotV);

	return light->color * NdotL * (diffuse + specular);
}

float BRDF::calculateFresnelReflectance(float ior, Intersection &intersection) {
	glm::vec3 norm = intersection.normal;
	if (dot(intersection.normal, intersection.ray.direction) > 0) {
		norm = -norm;
	}
		
	return fresnel(ior, norm, -intersection.ray.direction);
}

float BRDF::fresnel(float n, glm::vec3 a, glm::vec3 b) {
	float F_z = pow(n-1.f, 2)/pow(n+1.f, 2);
	return F_z + (1.f-F_z) * pow(1.f-dot(a, b), 5.f);
}

void BRDF::createParentNode(printNode* parent, Intersection in) {
	if (parent != nullptr) {
		parent->in = in;
		parent->ambient = glm::vec3(0, 0, 0);
		parent->diffuse = glm::vec3(0, 0, 0);
		parent->specular = glm::vec3(0, 0, 0);
	}
}

void BRDF::updateParentNode(printNode* parent, float local, float refl, float refr, glm::vec3 col) {
	if (parent == nullptr) {
		return;
	}

	parent->local_con = local;
	parent->refl_con = refl;
	parent->refr_con = refr;
	parent->final_color = col;
}

void BRDF::updateParentNode(printNode* parent, Ray &ray, glm::vec3 color, int type) {
	if (parent == nullptr) {
		return;
	}
	if (type) {
		parent->refraction_d = ray.direction;
	}
	else {
		parent->reflection_d = ray.direction;
	}
}

BRDF::printNode* BRDF::createChildNode(printNode* parent, int type) {
	if (parent == nullptr) {
		return nullptr;
	}

	printNode* child = new printNode;
	// Reflection
	if (type == 0) {
		child->type = "Reflection";
		parent->refl = child;
	}
	// Refraction
	else {
		child->type = "Refraction";
		parent->refr = child;
	}
	return child;
}
