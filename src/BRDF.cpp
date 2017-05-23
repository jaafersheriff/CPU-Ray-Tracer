#include "BRDF.hpp"

const static float EPSILON = 0.0001f;


glm::vec3 BRDF::raytrace(Scene &scene, Ray &incident_ray, int recurse_count, printNode* parent) {
   // Base case
   if (recurse_count <= 0) {
      return glm::vec3(0, 0, 0);
   }

   // If no intersection from camera to object, return black
   Intersection incident_int(scene.objects, incident_ray);
   if (!incident_int.hit) {
      return glm::vec3(0, 0, 0);
   }

   // Easing variable names
   GeoObject::Finish *finish = &incident_int.object->finish;

   // Verbose printing
   createParentNode(parent, incident_int);

   // Colors
   glm::vec3 local_color = calculateLocalColor(scene, incident_int, parent);
   glm::vec3 reflection_color = calculateReflectionColor(scene, incident_int, recurse_count, parent);
   glm::vec3 refraction_color = calculateRefractionColor(scene, incident_int, recurse_count, parent);

   // Fresnel
	float fresnel_reflectance = 0.f;
	if (fresnel_flag) {
		fresnel_reflectance = calculateFresnelReflectance(finish->ior, incident_int);
	}

   // Contributions 
   float local_contribution = (1.f - finish->filter) * (1.f - finish->reflection);
   float reflectance_contribution = (1.f - finish->filter) * (finish->reflection) + (finish->filter) * (fresnel_reflectance);
   float transmission_contribution = (finish->filter) * (1 - fresnel_reflectance);

   return local_color * local_contribution +
          reflection_color * reflectance_contribution +
          refraction_color * transmission_contribution;
}

glm::vec3 BRDF::calculateLocalColor(Scene &scene, Intersection &intersection, printNode* parent) {
   // Ambient
   glm::vec3 local_color = intersection.object->finish.color * intersection.object->finish.ambient;
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
      Intersection light_int(scene.objects, light_ray);
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
   glm::vec3 refraction_color = raytrace(scene, refraction_ray, recurse-1, createChildNode(parent, 1));

   // Beers law
   Intersection i = Intersection(scene.objects, refraction_ray);
   if (i.hit) {
      float dist = glm::distance(i.point, refraction_ray.position);
      glm::vec3 absorb = (1.f - intersection.object->finish.color) * (0.15f) * -dist;
      glm::vec3 atten = glm::vec3(exp(absorb.r), exp(absorb.g), exp(absorb.b));
      refraction_color *= atten;
   }

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

void BRDF::createParentNode(printNode* parent, Intersection in) {
   if (parent != nullptr) {
      parent->in = in;
      parent->ambient = glm::vec3(0, 0, 0);
      parent->diffuse = glm::vec3(0, 0, 0);
      parent->specular = glm::vec3(0, 0, 0);
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

float BRDF::calculateFresnelReflectance(float ior, Intersection &intersection) {
	if (dot(intersection.ray.direction, intersection.normal) > 0) {
		return fresnel(ior, -intersection.normal, -intersection.ray.direction);
	}
	else {
		return fresnel(ior, intersection.normal, -intersection.ray.direction);
	}
}

float BRDF::fresnel(float n, glm::vec3 a, glm::vec3 b) {
   float F_z = pow(n-1.f, 2)/pow(n+1.f, 2);
   return F_z + (1.f-F_z) * pow(1.f-dot(a, b), 5.f);
}
