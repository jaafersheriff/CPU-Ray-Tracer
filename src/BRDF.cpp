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
   glm::vec3 norm = incident_int.object->findNormal(incident_int.point);

   // Verbose printing
   createParentNode(parent, incident_int, norm);

   // Colors
   glm::vec3 local_color = calculateLocalColor(scene, incident_int, norm, parent);
   glm::vec3 reflection_color = calculateReflectionColor(scene, incident_int, norm, recurse_count, parent);
   glm::vec3 refraction_color = calculateRefractionColor(scene, incident_int, norm, recurse_count, parent);

	// Contributions 
   float fresnel_reflectance = fresnel(finish->ior, norm, -incident_ray.direction);
   float local_contribution = (1.f - finish->filter) * (1.f - finish->reflection);
   float reflectance_contribution = (1.f - finish->filter) * (finish->reflection) + (finish->filter) * (fresnel_reflectance);
   float transmission_contribution = (finish->filter) * (1 - fresnel_reflectance);

   return local_color * local_contribution +
          reflection_color * reflectance_contribution +
          refraction_color * transmission_contribution;
}


glm::vec3 BRDF::calculateLocalColor(Scene &scene, Intersection &intersection, glm::vec3 norm, printNode* parent) {
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
         local_color += render_flag ? CookTorrance(light, intersection, norm) : BlinnPhong(light, intersection, norm, parent);
      }
 
		// Verbose printing
      if (parent != nullptr) {
         parent->shadow_ray = light_ray;
      }
   }

   return local_color;
}

glm::vec3 BRDF::calculateReflectionColor(Scene &scene, Intersection &intersection, glm::vec3 norm, int recurse, printNode* parent) {
   if (!intersection.object->finish.reflection) {
      return glm::vec3(0, 0, 0);
   }

   Ray reflection_ray = createReflectionRay(intersection, norm);
   glm::vec3 reflection_color = raytrace(scene, reflection_ray, recurse-1, createChildNode(parent, 0));

   return reflection_color;
}

Ray BRDF::createReflectionRay(const Intersection &intersection, const glm::vec3 norm) {
   const Ray incident_ray = intersection.ray;
   const glm::vec3 incident_point = intersection.point;

   glm::vec3 reflection_dir = normalize(incident_ray.direction - 2 * dot(incident_ray.direction, norm) * norm);
	glm::vec3 p_z = incident_point + reflection_dir * EPSILON;
   return Ray(p_z, reflection_dir);
}

glm::vec3 BRDF::calculateRefractionColor(Scene &scene, Intersection &intersection, glm::vec3 norm, int recurse, printNode* parent) {
   if (!intersection.object->finish.filter) {
      return glm::vec3(0, 0, 0);
   }

   Ray refraction_ray = createRefractionRay(intersection.object->finish.ior, intersection.ray, intersection.point, norm);
   glm::vec3 refraction_color = raytrace(scene, refraction_ray, recurse-1, createChildNode(parent, 1));

   // Beers law
   Intersection i = Intersection(scene.objects, refraction_ray);
   if (i.hit) {
      float dist = glm::distance(i.point, refraction_ray.position);
      glm::vec3 absorb = (1.f - i.object->finish.color) * (0.15f) * -dist;
      glm::vec3 atten = glm::vec3(exp(absorb.r), exp(absorb.g), exp(absorb.b));
      refraction_color *= atten;
   }

   return refraction_color;
}

Ray BRDF::createRefractionRay(const float ior, const Ray &in_ray, const glm::vec3 pos, glm::vec3 norm) {
   float n1 = 1;
   float n2 = ior;
   // If we're 'exiting' an object
   if (dot(norm, in_ray.direction) > 0) {
      n1 = ior;
      n2 = 1;
      norm = -norm;
   }
   
	float dDotN = dot(in_ray.direction, norm);
   float rat = n1/n2;
   float root = 1-(rat*rat)*(1-dDotN*dDotN);

   glm::vec3 refraction_dir = normalize(rat*(in_ray.direction-dDotN*norm)-norm*(float)sqrt(root));
	glm::vec3 p_z = pos + refraction_dir * EPSILON;
   return Ray(p_z, refraction_dir);
}

glm::vec3 BRDF::BlinnPhong(Light *light, Intersection &object_in, glm::vec3 norm, printNode* p) {
   GeoObject::Finish *finish = &object_in.object->finish;
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float HdotN = std::max(0.f, dot(half, norm));

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

glm::vec3 BRDF::CookTorrance(Light *light, Intersection &object_in, glm::vec3 norm) {
   GeoObject::Finish *finish = &object_in.object->finish;
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float HdotN = std::max(0.f, dot(half, norm));
   float NdotV = std::max(0.f, dot(norm, -object_in.ray.direction));
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

void BRDF::createParentNode(printNode* parent, Intersection in, glm::vec3 norm) {
   if (parent != nullptr) {
      parent->in = in;
      parent->norm = norm;
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

float BRDF::fresnel(float n, glm::vec3 a, glm::vec3 b) {
   float F_z = pow(n-1.f, 2)/pow(n+1.f, 2);
   return F_z + (1.f-F_z) * pow(1.f-dot(a, b), 5.f);
}
