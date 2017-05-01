#include "BRDF.hpp"

glm::vec3 BlinnPhong(Light *light, Intersection &object_in) {
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 norm = object_in.object->findNormal(object_in.point);
   glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float HdotN = std::max(0.f, dot(half, norm));
   
   // Diffuse
   glm::vec3 diffuse;
   if (!NdotL || !object_in.object->diffuse) {
      diffuse = glm::vec3(0, 0, 0);
   }
   else {
      diffuse = object_in.object->diffuse * object_in.object->color * NdotL * light->color;
   }

   // Specular
   glm::vec3 specular;
   if (!HdotN || !object_in.object->specular) {
      specular = glm::vec3(0, 0, 0);
   }
   else {
      float r_squared = object_in.object->roughness*object_in.object->roughness;
      specular = object_in.object->specular * object_in.object->color  * (float) pow(HdotN, 2/r_squared - 2) * light->color;      
   }

   return diffuse + specular;
}

glm::vec3 CookTorrance(Light *light, Intersection &object_in) {
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 norm = object_in.object->findNormal(object_in.point);
   glm::vec3 half = glm::normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float HdotN = std::max(0.f, dot(half, norm));
   float NdotV = std::max(0.f, dot(norm, -object_in.ray.direction));
   float VdotH = std::max(0.f, dot(-object_in.ray.direction, half));

   if (NdotL == 0.f) {
      return glm::vec3(0, 0, 0);
   }

   // Diffuse
   glm::vec3 diffuse = object_in.object->color * (1-object_in.object->metallic);

   // Specular
   // D - Blinn
   float D = 0.f;
   if (HdotN > 0.f && object_in.object->roughness > 0.f) {
      float r_squared = object_in.object->roughness*object_in.object->roughness;
      D = pow(HdotN, 2/(r_squared*r_squared) - 2)/(PI * r_squared*r_squared);
   }

   // G
   float G = 1.f;
   G = std::min(G, 2.f*HdotN*NdotV/VdotH);
   G = std::min(G, 2.f*HdotN*NdotL/VdotH);

   // F
   float F_z = pow(object_in.object->ior-1.f, 2.f)/pow(object_in.object->ior+1.f, 2.f);
   float F = F_z + (1.f-F_z) * pow(1.f-VdotH, 5.f);

   glm::vec3 specular = object_in.object->color * object_in.object->metallic;
   specular *= (D*G*F) / (4.f*NdotL*NdotV);


   return light->color * NdotL * (diffuse + specular);
}

