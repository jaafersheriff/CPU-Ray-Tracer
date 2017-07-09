#include "Renderer.hpp"

#include <algorithm>
#include <thread> // multiple threads

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

void Renderer::threadRender(thread_data *td) {
   float count = 0;
   int startX = (int) std::floor(td->index *td->size.x / td->num_threads);
   int endX   = (int) std::ceil((td->index+1) *td->size.x / td->num_threads);

   std::cout << "Thread " << td->index << ": [" << startX << ", " << endX << "}" << std::endl;
   for (int x = startX; x < endX; x++) {
      // Print percentages
      if (percent_flag) {
         std::cerr << "Thread " << td->index << ": " << count/((endX-startX)*td->size.y)*100 << "%" << std::endl;
      }
      for (int y = 0; y < td->size.y; y++) {
         count++;

         // Calculate color
         glm::vec3 color = calculateColor(*td->scene, td->size, x, y);

         // Set pixel color
         unsigned char red   = (unsigned char) color.r; 
         unsigned char green = (unsigned char) color.g; 
         unsigned char blue  = (unsigned char) color.b; 
         int pixel = (td->size.x * td->numChannels) * (td->size.y - 1 - y) + td->numChannels * x;
         td->data[pixel + 0] = red;
         td->data[pixel + 1] = green;
         td->data[pixel + 2] = blue;
      }
   }
}

void Renderer::render(Scene &scene, const int window_width, const int window_height, const int num_threads) {
   const int numChannels = 3;
   const glm::ivec2 size = glm::ivec2(window_width, window_height);

   unsigned char *data = new unsigned char[size.x * size.y * numChannels];

   // Create threads
   std::vector<std::thread> threads;
   struct thread_data td[num_threads];
   
   for (int i = 0; i < num_threads; i++) {
      td[i].scene = &scene;
      td[i].size = size;
      td[i].numChannels = numChannels;
      td[i].data = data;
      td[i].index = i;
      td[i].num_threads = num_threads;
      threads.push_back(std::thread(&Renderer::threadRender, this, &td[i]));
   }
   for (auto& thread : threads) {
      thread.join();
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

