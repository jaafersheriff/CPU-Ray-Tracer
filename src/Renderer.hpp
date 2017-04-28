// Renderer class
// Takes in a Scene and renders it
#ifndef _RENDERER_H_
#define _RENDERER_H_

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

	void render(Scene &, const int, const int);
};

#endif
