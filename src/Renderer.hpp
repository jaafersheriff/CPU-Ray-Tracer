// Renderer class
// Takes in a Scene and renders it
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "Intersection.hpp"

class Renderer {
public:

   // 0 - Blinn-Phong
   // 1 - Cook-Trrance
   int BRDF;

	Renderer() {
      BRDF = 0;
   };

   glm::vec3 findColor(Scene &, const glm::ivec2, const int, const int);
	void render(Scene &, const int, const int);
private:

   glm::vec3 cookTorrance(Intersection &);
   glm::vec3 blinnPhong(Scene &, Intersection &, Ray &);
};

#endif
