#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Intersection.hpp"
#include "Scene.hpp"

#define PI 3.14159265359f

class BRDF {
public:
   struct printNode {
      std::string type;
      Intersection in;
      Ray shadow_ray;
      glm::vec3 norm;
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

   glm::vec3 raytrace(Scene &, Ray &, int, printNode*);

   float fresnel(float, glm::vec3, glm::vec3);


   glm::vec3 calculateLocalColor(Scene &, Intersection &, glm::vec3, printNode*);

   glm::vec3 calculateReflectionColor(Scene &, Intersection &, glm::vec3, float, int, printNode*);
	Ray createReflectionRay(const Intersection &, const glm::vec3);

   glm::vec3 calculateRefractionColor(Scene &, Intersection &, glm::vec3, float, int, printNode*);
   Ray createRefractionRay(const float, const Ray &, const glm::vec3, glm::vec3);


	glm::vec3 BlinnPhong(Light *, Intersection &, glm::vec3, printNode*);
	glm::vec3 CookTorrance(Light *, Intersection &, glm::vec3);

   void createParentNode(printNode*, Intersection, glm::vec3);
   printNode* createChildNode(printNode*, int);

};

#endif
