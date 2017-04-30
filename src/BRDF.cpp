#include "BRDF.hpp"

glm::vec3 BlinnPhong(Light *light, Intersection &object_in) {
   glm::vec3 light_dir = normalize(light->position - object_in.point);
   glm::vec3 norm = object_in.object->findNormal(object_in.point);
   glm::vec3 half = normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float HdotN = std::max(0.f, dot(half, norm));   
   
   // Diffuse
   glm::vec3 ret = NdotL * object_in.object->color * object_in.object->diffuse * light->color;

   // Specular
   glm::vec3 specular = object_in.object->color * object_in.object->specular * light->color;
   ret += specular * (float) pow(HdotN, object_in.object->shininess);

   return ret;
}

glm::vec3 CookTorrance(Light *light, Intersection &object_in) {
   glm::vec3 light_dir = glm::normalize(light->position - object_in.point);
   glm::vec3 norm = object_in.object->findNormal(object_in.point);
   glm::vec3 half = normalize(light_dir - object_in.ray.direction);
   float NdotL = std::max(0.f, dot(norm, light_dir));
   float NdotV = std::max(0.f, dot(norm, -object_in.ray.direction));
   float HdotN = std::max(0.f, dot(half, norm));
   float VdotH = std::max(0.f, dot(-object_in.ray.direction, half));

   if (NdotL == 0.0f) {
      return glm::vec3(0, 0, 0);
   }

   // Diffuse
   glm::vec3 diffuse = object_in.object->color * (1-object_in.object->metallic);

   // Specular
   // D
   float D = 0;
   if (HdotN > 0 && object_in.object->roughness > 0) {
      float r_squared = object_in.object->roughness*object_in.object->roughness;
      D = pow(HdotN, 2/(r_squared*r_squared) - 2);
      D /= (PI * r_squared * r_squared);
   }
   // G
   float G = 1;
   if (VdotH > 0 && NdotV > 0 && HdotN > 0) {
      G = std::min(G, 2*HdotN*NdotV/VdotH);
      G = std::min(G, 2*HdotN*NdotL/VdotH);
   }

   // F
   float F_z = 0.2f;    // TODO: f_z = index of refraction
   float F = F_z + (1-F_z) * pow(1-VdotH, 5);

   glm::vec3 specular = object_in.object->color * (D*G*F) / (4*NdotL*NdotV);

   // s
   specular *= object_in.object->metallic;

   return light->color * NdotL * (diffuse + specular);
}

