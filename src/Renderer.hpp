// Renderer class
// Takes in a Scene and renders it

#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream> // cout
#include <glm/glm.hpp>

#include "Scene.hpp"
#include "BRDF.hpp"

#define OUTPUT_NAME "output.png"

#define RECURSE_COUNT 6

class Renderer {
public:
   // TODO : Move thread stuff elsewhere
   struct thread_data{
      Scene *scene;
      glm::ivec2 size;
      int numChannels;
      unsigned char *data;
      int index;
      int num_threads;
   };

   // Output file name
   std::string fileName = OUTPUT_NAME;

   // BRDF object for recursive raytracing
   BRDF brdf;

   // 0 - don't print
   // 1 - print
   int percent_flag = 0;

   // Super-sample count
   int SSCount = 1;
   void setSSCount(const int in) { this->SSCount = in; }

   // Global Illumination values
   void setGIFlag(int flag) { brdf.gi_flag = flag; }
   void setGISamples(int n) { brdf.gi_samples = n; }
   void setGIBounces(int n) { brdf.gi_bounces = n; }
   void setGIRatio(int n) { brdf.gi_ratio = n; }

   void render(Scene &, const int, const int, const int);
   void threadRender(thread_data *);
   glm::vec3 calculateColor(Scene &, const glm::ivec2, const int, const int);

   void print();
   void pixeltrace(int);
   void printrays(int);

   void setVerbose(int flag) { brdf.verbose_flag = flag; }
   void setFresnelFlag(int flag) { brdf.fresnel_flag = flag; }
   void setSpatialFlag(int flag) { brdf.spatial_flag = flag; }
   void setPercentFlag(int flag) { percent_flag = flag; }
   void setOutputName(char *name) { fileName = std::string(name); }
};

#endif
