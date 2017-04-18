// Renderer class
// Takes in a Scene and renders it
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glm/glm.hpp>

#include "Scene.h"
#include "Intersection.h"

class Renderer {
public:
	Renderer() {};

   glm::vec3 findColor(Scene &, const glm::ivec2, const int, const int);
	void render(Scene &, const int, const int);
};

#endif
