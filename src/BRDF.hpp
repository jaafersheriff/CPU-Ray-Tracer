#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Intersection.hpp"
#include "Scene.hpp"

#define PI 3.14159265359f

class BRDF {
public:
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

	void createReflectionRay(Ray *ray, const Intersection &intersection, const glm::vec3 norm);

	void createRefractionRay(Ray *ray, const float ior, const Ray &in_ray, const glm::vec3 p, glm::vec3 n);

	glm::vec3 raytrace(Scene &, Ray &, int);

	glm::vec3 BlinnPhong(Light *, Intersection &, glm::vec3);

	glm::vec3 CookTorrance(Light *, Intersection &, glm::vec3);

   float fresnel(float n, glm::vec3, glm::vec3);
};

#endif
