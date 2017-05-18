// Renderer class
// Takes in a Scene and renders it

#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream> // cout
#include <glm/glm.hpp>

#include "Scene.hpp"
#include "BRDF.hpp"

// Number of times to recurse when reflecting/refracting
#define RECURSE_COUNT 6

class Renderer {
public:
	// BRDF object for recursive raytracing
   BRDF brdf;

	// printNode object for verbose printing
   BRDF::printNode *root = nullptr;

   void render(Scene &, const int, const int); 
   glm::vec3 calculateColor(Scene &, const glm::ivec2, const int, const int);

   void print(); 
   void printRays(BRDF::printNode*, int level);
   
	void setBRDFVerbose(int flag) { brdf.verbose_flag = flag; }
   void setBRDFFlag(int flag) { brdf.render_flag = flag; }
};

#endif
