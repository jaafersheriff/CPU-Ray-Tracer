#include "BRDF.hpp"

glm::vec3 BRDF(std::vector<GeoObject *> objects, std::vector<Light *> lights, Ray &incident_ray, const int BRDF_flag, int recurse_count) {

   // Base case
   if (recurse_count < 0) {
      return glm::vec3(0, 0, 0);
   }

   // If no intersection from camera to object, return black
   Intersection incident_int(objects, incident_ray);
   if (!incident_int.hit()) {
      return glm::vec3(0, 0, 0);
   }

   GeoObject::Finish* finish = &incident_int.object->finish;

   // Ambient
   glm::vec3 local_color = incident_int.object->color * finish->ambient;

   // Calculate ray from object to each light
   glm::vec3 norm = incident_int.object->findNormal(incident_int.point);
   for (unsigned int i = 0; i < lights.size(); i++) {
      Light *light = lights[i];
      glm::vec3 light_dir = glm::normalize(light->position - incident_int.point);
      Ray light_ray(incident_int.point, light_dir);
      Intersection light_int(objects, light_ray);

      // If no objects are blocking incoming light, BRDF
      if (!light_int.hit() || distance(incident_int.point, light->position) < distance(incident_int.point, light_int.point)) {
         // Local color
         local_color += BRDF_flag ? CookTorrance(light, incident_int, norm) : BlinnPhong(light, incident_int, norm);
      }
   }

   // Reflection color
   Ray reflection_ray;
   createReflectionRay(&reflection_ray, incident_int, norm);
   glm::vec3 reflection_color = BRDF(objects, lights, reflection_ray, BRDF_flag, recurse_count-1);

   // Refraction color
   // Refraction inside of object
   Ray inner_refraction_ray;
   createRefractionRay(&inner_refraction_ray, 1, finish->ior, incident_ray, incident_int.point, norm);
   glm::vec3 refraction_color = BRDF(objects, lights, inner_refraction_ray, BRDF_flag, recurse_count-1);
   // Refraction outside of object
   float t = incident_int.object->intersect(inner_refraction_ray);
   glm::vec3 p = inner_refraction_ray.intersection_point(t);
   Ray outer_refraction_ray;
   createRefractionRay(&outer_refraction_ray, finish->ior, 1, inner_refraction_ray, p, -norm);
   refraction_color += BRDF(objects, lights, outer_refraction_ray, BRDF_flag, recurse_count-1);

   // Fresnel
   // TODO: functional programming
   float NdotV = dot(norm, -incident_int.ray.direction);
   float F_z = pow(finish->ior-1, 2)/pow(finish->ior+1, 2);
   float fresnel_reflectance = F_z + (1 - F_z) * pow(1-NdotV, 5);

   float local_contribution = (1-finish->filter) * (1-finish->reflection);
   float reflectance_contribution = (1-finish->filter) * finish->reflection * finish->filter * fresnel_reflectance;
   float transmission_contribution = finish->filter * (1-fresnel_reflectance);

   return local_contribution*local_color +
          reflectance_contribution * reflection_color +
          transmission_contribution * refraction_color;
}

void createReflectionRay(Ray *ray, const Intersection &intersection, const glm::vec3 norm) {
   const Ray incident_ray = intersection.ray;
   const glm::vec3 incident_point = intersection.point;

   glm::vec3 reflection_dir = incident_ray.direction - 2 * dot(incident_ray.direction, norm) * norm;

   // TODO: setter
   ray->position = glm::vec3(incident_point);
   ray->direction = glm::vec3(reflection_dir);
}

void createRefractionRay(Ray *ray, const float n1, const float n2, const Ray &in_ray, const glm::vec3 p, const glm::vec3 n) {
   float dDotN = dot(in_ray.direction, n);
   float rat = n1/n2;
   float root = 1-rat*rat*(1-dDotN*dDotN);

   // TODO - user setter
   ray->position = p;
   ray->direction = glm::vec3(rat*(in_ray.direction-dDotN*n)-n*(float)sqrt(root));
}

glm::vec3 BlinnPhong(Light *light, Intersection &object_in, glm::vec3 norm) {
   GeoObject::Finish *finish = &object_in.object->finish;
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float HdotN = std::max(0.f, dot(half, norm));

   // Diffuse
   glm::vec3 diffuse = glm::vec3(0, 0, 0);
   if (NdotL && finish->diffuse) {
      diffuse = finish->diffuse * object_in.object->color * NdotL * light->color;
   }

   // Specular
   glm::vec3 specular = glm::vec3(0, 0, 0);;
   if (HdotN && finish->specular) {
      float r_squared = finish->roughness*finish->roughness;
      specular = finish->specular * object_in.object->color  * (float) pow(HdotN, 2/r_squared - 2) * light->color;
   }

   return diffuse + specular;
}

glm::vec3 CookTorrance(Light *light, Intersection &object_in, glm::vec3 norm) {
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
   glm::vec3 diffuse = object_in.object->color * (1 - finish->metallic);

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
   float F_z = pow(finish->ior-1.f, 2.f)/pow(finish->ior+1.f, 2.f);
   float F = F_z + (1.f-F_z) * pow(1.f-VdotH, 5.f);

   glm::vec3 specular = object_in.object->color * finish->metallic;
   specular *= (D*G*F) / (4.f*NdotL*NdotV);


   return light->color * NdotL * (diffuse + specular);
}

