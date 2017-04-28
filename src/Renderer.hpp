// Renderer class
// Takes in a Scene and renders it
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream> 
#include <glm/glm.hpp>

#include "Scene.hpp"

class Renderer {
public:

   // 0 - Blinn-Phong
   // 1 - Cook-Torrance
   int BRDF_flag;

	Renderer() {
      BRDF_flag = 0;
   };

   glm::vec3 calculateColor(Scene &, const glm::ivec2, const int, const int, int);
	
   void render(Scene &, const int, const int);

   void print();
};

#endif
