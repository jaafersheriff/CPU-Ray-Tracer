// Renderer class
// Takes in a Scene and renders it
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <glm/glm.hpp>

#include "Scene.hpp"
#include "BRDF.hpp"

// Number of times to recurse when reflecting/refracting
#define RECURSE_COUNT 6

class Renderer {
public:
   BRDF brdf;

   void setBRDFVerbose(int flag) {
      brdf.verbose_flag = flag;
   }

   void setBRDFFlag(int flag) {
      brdf.render_flag = flag;
   }

   glm::vec3 calculateColor(Scene &, const glm::ivec2, const int, const int);

   void render(Scene &, const int, const int);

   BRDF::printNode *root = nullptr;
   void print();
   void printRays(BRDF::printNode*, int level);
};

#endif
