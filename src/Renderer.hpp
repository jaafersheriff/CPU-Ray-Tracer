// Renderer class
// Takes in a Scene and renders it

#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream> // cout
#include <glm/glm.hpp>

#include "Scene.hpp"
#include "BRDF.hpp"

#define RECURSE_COUNT 6

class Renderer {
public:
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

   // printNode object for verbose printing
   BRDF::printNode *root = nullptr;

   void render(Scene &, const int, const int);
   glm::vec3 calculateColor(Scene &, const glm::ivec2, const int, const int);

   void print();
   void pixeltrace(BRDF::printNode*, int );
   void printrays(BRDF::printNode*, int);

   void setVerbose(int flag) { brdf.verbose_flag = flag; }
   void setRenderFlag(int flag) { brdf.render_flag = flag; }
   void setFresnelFlag(int flag) { brdf.fresnel_flag = flag; }
   void setSpatialFlag(int flag) { brdf.spatial_flag = flag; }
   void setPercentFlag(int flag) { percent_flag = flag; }
};

#endif
