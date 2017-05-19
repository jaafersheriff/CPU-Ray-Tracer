// Recursive BRDF class
// Recursive reflection/refraction ray calculation and color calculations 
#pragma once
#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Intersection.hpp"
#include "Scene.hpp"

#define PI 3.14159265359f

class BRDF {
public:
	// Used for verbose printing
   struct printNode {
      std::string type;
      Intersection in;
      Ray shadow_ray;
      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;
      printNode *refr = nullptr;
      printNode *refl = nullptr;
   };

   // 0 - No ray printing
   // 1 - Ray printing
   int verbose_flag;

	// 0 - Blinn-Phong
   // 1 - Cook-Torrance
   int render_flag;

	BRDF() {
      render_flag = 0;
      verbose_flag = 0;
   };

	// Master recursive function for tracing rays
   glm::vec3 raytrace(Scene &, Ray &, int, printNode*);


	// Color calculation functions
   glm::vec3 calculateLocalColor(Scene &, Intersection &, printNode*);
   glm::vec3 calculateReflectionColor(Scene &, Intersection &, int, printNode*);
   glm::vec3 calculateRefractionColor(Scene &, Intersection &, int, printNode*);

	// Ray calculation functions
	Ray createReflectionRay(const Intersection &);
   Ray createRefractionRay(const Intersection &);

	// Shading calculations
	glm::vec3 BlinnPhong(Light *, Intersection &, printNode*);
	glm::vec3 CookTorrance(Light *, Intersection &);

	// Verbose printing
   void createParentNode(printNode*, Intersection);
   printNode* createChildNode(printNode*, int);

	// Helpers
   float fresnel(float, glm::vec3, glm::vec3);
};

#endif
