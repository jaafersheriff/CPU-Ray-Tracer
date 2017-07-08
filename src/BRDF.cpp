#include "BRDF.hpp"

#include "glm/gtc/matrix_transform.hpp"	// Matrix transformations
#include <algorithm>

const static float EPSILON = 0.0001f;

glm::vec3 BRDF::raytrace(Scene &scene, Ray &incident_ray, int recurse_count) {
	// Base case
	if (recurse_count <= 0) {
		return glm::vec3(0, 0, 0);
	}

  // If no intersection from camera to object, return black
	Intersection incident_int(scene, incident_ray, spatial_flag);
	if (!incident_int.hit) {
		return glm::vec3(0, 0, 0);
	}

	return calculateColor(scene, incident_int, recurse_count);
}

glm::vec3 BRDF::calculateColor(Scene &scene, Intersection &intersection, int recurse_count) {
	// Base case
	if (recurse_count <= 0 || !intersection.hit) {
		return glm::vec3(0, 0, 0);
	}

	// Easing variable names
	GeoObject::Finish *finish = &intersection.object->finish;

	// Colors
	glm::vec3 local_color 		= calculateLocalColor(scene, intersection, recurse_count);
	glm::vec3 reflection_color = calculateReflectionColor(scene, intersection, recurse_count);
	glm::vec3 refraction_color = calculateRefractionColor(scene, intersection, recurse_count);

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

	return out_color;
}

glm::vec3 BRDF::calculateLocalColor(Scene &scene, Intersection &intersection, int recurse_count) {
  if (intersection.object->textures.colorMap != nullptr) {
		intersection.pigment = intersection.object->textures.colorMap->getColor(intersection.object->getUVCoords(intersection.objectPoint));
	}
	else {
		intersection.pigment = intersection.object->finish.color;
	} 

	glm::vec3 local_color = glm::vec3(0, 0, 0);

	// Ambient
	if (!gi_flag) {
      local_color = intersection.object->finish.ambient * intersection.pigment;
   } 
   else {
	   // Global illumination
	   if (gi_bounces < recurse_count) {
	   	recurse_count = gi_bounces;
	   } 
	   else {
		   recurse_count--;
   	}     
      local_color = calculateGlobalIllumination(scene, intersection, recurse_count);
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
			local_color += BlinnPhong(light, intersection);
		}
	}

	return local_color;
}

glm::vec3 BRDF::calculateGlobalIllumination(Scene &scene, Intersection &intersection, int recurse_count) {
   glm::vec3 out_color = glm::vec3(0, 0, 0);
	int num_samples = gi_samples;

	if (gi_bounces - recurse_count > 0) {
		num_samples /= ((gi_bounces - recurse_count) * gi_ratio);
	}

	float angle = glm::acos(glm::dot(glm::vec3(0, 0, 1), intersection.normal));
	glm::vec3 axis = glm::cross(glm::vec3(0, 0, 1), intersection.normal);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), angle, axis);	
   
   float root_num_samples = std::sqrt(num_samples);
   float ratio = root_num_samples / num_samples;

   // Stratified samples 
   for (float x = 0.f; x <= num_samples; x += root_num_samples) {
      for (float y = 0.f; y <= num_samples; y += root_num_samples) {
         float gridX = x / num_samples + ratio * (rand() / (float) RAND_MAX);
         float gridY = y / num_samples + ratio * (rand() / (float) RAND_MAX);
  
         glm::vec3 sample_point = scene.createSamplePoint(intersection, matrix, gridX, gridY);
         Ray sample_ray(intersection.point + sample_point * EPSILON, sample_point);
         out_color += raytrace(scene, sample_ray, recurse_count);
      }
   } 

   return out_color / (float) num_samples;
}

glm::vec3 BRDF::calculateReflectionColor(Scene &scene, Intersection &intersection, int recurse) {
	if (!intersection.object->finish.reflection) {
		return glm::vec3(0, 0, 0);
	}

	Ray reflection_ray = scene.createReflectionRay(intersection);
	glm::vec3 reflection_color = raytrace(scene, reflection_ray, recurse-1);

	// Reflection color is scaled by object's material
	reflection_color *= intersection.pigment;

	return reflection_color;
}

glm::vec3 BRDF::calculateRefractionColor(Scene &scene, Intersection &intersection, int recurse) {
	if (!intersection.object->finish.filter) {
		return glm::vec3(0, 0, 0);
	}

	Ray refraction_ray = scene.createRefractionRay(intersection);
	Intersection ref_intersection = Intersection(scene, refraction_ray, spatial_flag);
	// If no intersection
	if (!ref_intersection.hit) {
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 refraction_color = calculateColor(scene, ref_intersection, recurse-1);

	// Beers law
	float dist = glm::distance(ref_intersection.point, intersection.point);
	glm::vec3 absorb = (1.f - intersection.pigment) * (0.15f) * -dist;
	glm::vec3 atten = glm::vec3( exp(absorb.r), exp(absorb.g), exp(absorb.b) );
	refraction_color *= atten;

	return refraction_color;
}


glm::vec3 BRDF::BlinnPhong(Light *light, Intersection &object_in) {
	// Initialize local vars
	GeoObject::Finish *finish = &object_in.object->finish;
	glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
	glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
	float NdotL = std::max(0.f, dot(object_in.normal, light_dir));
	float HdotN = std::max(0.f, dot(half, object_in.normal));

	// Diffuse
	glm::vec3 diffuse = glm::vec3(0, 0, 0);
	if (NdotL && finish->diffuse) {
		diffuse = finish->diffuse * NdotL * light->color * object_in.pigment;
	}

	// Specular
	glm::vec3 specular = glm::vec3(0, 0, 0);;
	if (HdotN && finish->specular) {
	   float r_squared = finish->roughness*finish->roughness;
	   specular = finish->specular * object_in.pigment * (float) pow(HdotN, 2/r_squared - 2) * light->color;
	}

	return diffuse + specular;
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

