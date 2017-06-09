#include "Renderer.hpp"
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

glm::vec3 Renderer::calculateColor(Scene &scene, const glm::ivec2 size, const int x, const int y) {
   if (brdf.verbose_flag) {
      root = new BRDF::printNode;
      root->type = "Primary";
   }

   // Calculate color
   glm::vec3 color = glm::vec3(0, 0, 0);
   for (int m = 0; m < SSCount; m++) {
      for (int n = 0; n < SSCount; n++) {
         Ray camera_ray = scene.createCameraRay(size.x, size.y, x, y, m, n, SSCount);
         color += brdf.raytrace(scene, camera_ray, RECURSE_COUNT, root);
      }
   }
   color /= (SSCount*SSCount);

   // Scale RGB from [0, 1] to [0, 255]
   color.r = round(glm::clamp(color.r, 0.f, 1.f) * 255.f);
   color.g = round(glm::clamp(color.g, 0.f, 1.f) * 255.f);
   color.b = round(glm::clamp(color.b, 0.f, 1.f) * 255.f);

   return color;
}

void Renderer::render(Scene &scene, const int window_width, const int window_height) {
   const int numChannels = 3;
   const glm::ivec2 size = glm::ivec2(window_width, window_height);

   unsigned char *data = new unsigned char[size.x * size.y * numChannels];

   float count = 0;
   for (int y = 0; y < size.y; y++) {
      for (int x = 0; x < size.x; x++) {
         // Print percentages
         if (percent_flag) {
            std::cerr << count++/(size.x*size.y)*100 << "%" << std::endl;
         }

         // Calculate color
         glm::vec3 color = calculateColor(scene, size, x, y);

         // Set pixel color
         unsigned char red   = (unsigned char) color.r;
         unsigned char green = (unsigned char) color.g;
         unsigned char blue  = (unsigned char) color.b;
         int pixel = (size.x * numChannels) * (size.y - 1 - y) + numChannels * x;
         data[pixel + 0] = red;
         data[pixel + 1] = green;
         data[pixel + 2] = blue;
      }
   }
   if (!stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels)) {
      std::cout << "FAILED WRITING IMAGE" << std::endl;
   }
   delete[] data;
}

void Renderer::print() {
   std::cout << "BRDF: ";
   if (brdf.render_flag)
      std::cout << "Cook-Torrance";
   else
      std::cout << "Blinn-Phong";
   std::cout << std::endl;
}

void Renderer::pixeltrace(BRDF::printNode* root, int level) {
   if (root == nullptr) {
      return;
   }

   if (level > 0) {
      for (int i = 1; i < level; i++) { std::cout << "  "; }
      std::cout << " \\" << std::endl;;
   }

   for (int i = 0; i < level; i++) { std::cout << "  "; }
   std::cout << "o - Iteration type: " << root->type << std::endl;

   for (int i = 0; i < level; i++) { std::cout << "  "; }
   std::cout << "|   Ray: "; root->in.ray.print();

   if (root->in.hit) {
      for (int i = 0; i < level; i++) { std::cout << "  "; }
      std::cout << "|   Hit Object ID (" << root->in.object->id << " - " << root->in.object->type << ") at T = " << root->in.t;
      std::cout << ", Intersection = {" << root->in.point.x << " " << root->in.point.y << " " << root->in.point.z << "}" << std::endl;

      for (int i = 0; i < level; i++) { std::cout << "  "; }
      std::cout << "|   Transformed Ray: "; root->in.ray.print();

      for (int i = 0; i < level; i++) { std::cout << "  "; }
      std::cout << "|   ShadowRay [0] "; root->shadow_ray.print();

      for (int i = 0; i < level; i++) { std::cout << "  "; }
      std::cout << "|   Ambient: " << root->ambient.x << ", " << root->ambient.y << ", " << root->ambient.z << std::endl;
      for (int i = 0; i < level; i++) { std::cout << "  "; }
      std::cout << "|   Diffuse: " << root->diffuse.x << ", " << root->diffuse.y << ", " << root->diffuse.z << std::endl;
      for (int i = 0; i < level; i++) { std::cout << "  "; }
      std::cout << "|   Specular: " << root->specular.x << ", " << root->specular.y << ", " << root->specular.z << std::endl;

   }
   for (int i = 0; i < level; i++) { std::cout << "  "; }
   std::cout << "|" << std::endl;

   pixeltrace(root->refr, level+1);
   pixeltrace(root->refl, level+1);
}

void Renderer::printrays(BRDF::printNode* root, int level) {
   if (root == nullptr) {
      return;
   }

   std::cout << "  Iteration type: " << root->type << std::endl;
   std::cout << "             Ray: ";
      root->in.ray.print();
   std::cout << " Transformed Ray: ";
      root->in.objectRay.print();
   std::cout << "      Hit Object: (ID #" << root->in.object->id << " - " << root->in.object->type << ")" << std::endl;
   std::cout << "    Intersection: {" << root->in.point.x << " " << root->in.point.y << " " << root->in.point.z << "}";
      std::cout << " at T = " << root->in.t << std::endl;
   std::cout << "          Normal: {" << root->in.normal.x << " " << root->in.normal.y << " " << root->in.normal.z << "}" << std::endl;
   std::cout << "         Ambient: {" << root->final_color.x << " " << root->final_color.y << " " << root->final_color.z << "}" << std::endl;
   std::cout << "         Diffuse: {" << root->diffuse.x << " " << root->diffuse.y << " " << root->diffuse.z << "}" << std::endl;
   std::cout << "        Specular: {" << root->specular.x << " " << root->specular.y << " " << root->specular.z << "}" << std::endl;
   std::cout << "      Reflection: {" << root->reflection_d.x << " " << root->reflection_d.y << " " << root->reflection_d.z << "}" << std::endl;
   std::cout << "      Refraction: {" << root->refraction_d.x << " " << root->refraction_d.y << " " << root->refraction_d.z << "}" << std::endl;;
   std::cout << "   Contributions: " << root->local_con << " Local, " << root-> refl_con << " Reflection, " << root->refr_con << " Transmission" << std::endl;
}
