#include "Renderer.hpp"
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

glm::vec3 Renderer::calculateColor(Scene &scene, const glm::ivec2 size, const int x, const int y) {
   // Calculate color
   glm::vec3 color = glm::vec3(0, 0, 0);
   for (int m = 0; m < SSCount; m++) {
      for (int n = 0; n < SSCount; n++) {
         Ray camera_ray = scene.createCameraRay(size.x, size.y, x, y, m, n, SSCount);
         color += brdf.raytrace(scene, camera_ray, RECURSE_COUNT);
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
      std::cout << "Blinn-Phong";
   std::cout << std::endl;
}

