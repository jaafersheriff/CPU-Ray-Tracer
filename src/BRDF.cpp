#include "BRDF.hpp"

glm::vec3 BlinnPhong(Light *light, Intersection &object_in) {
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 norm = object_in.object->findNormal(object_in.point);
   glm::vec3 half = glm::normalize(light_dir - glm::normalize(object_in.ray.direction));
   float NdotL = dot(norm, light_dir);
   float HdotN = dot(half, norm);   
   
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
   float NdotL = dot(norm, light_dir);
   float NdotV = dot(norm, -object_in.ray.direction);
   float HdotN = dot(half, norm);
   float VdotH = dot(-object_in.ray.direction, half);

   if (NdotL == 0.0f) {
      return glm::vec3(0, 0, 0);
   }

   // Diffuse
   glm::vec3 diffuse = object_in.object->color * (1-object_in.object->metallic);

   // Specular
   // D
   float D = 0;
   if (!HdotN && !object_in.object->roughness) {
      float r_squared = object_in.object->roughness*object_in.object->roughness;
      D = pow(HdotN, 2/(r_squared*r_squared) - 2);
      D /= (PI * r_squared*r_squared);
   }
   // G
   float G = 1;
   if (!VdotH && !NdotV && !HdotN) {
      G = std::min(G, 2*HdotN*NdotV/VdotH);
      G = std::min(G, 2*HdotN*NdotL/VdotH);
   }

   // F
   float F_z = pow(object_in.object->ior-1, 2)/pow(object_in.object->ior+1, 2);
   float F = F_z + (1-F_z) * pow(1-VdotH, 5);

   glm::vec3 specular = object_in.object->color * (D*G*F) / (4*NdotL*NdotV);

   // s
   specular *= object_in.object->metallic;

   return light->color * NdotL * (diffuse + specular);
}

