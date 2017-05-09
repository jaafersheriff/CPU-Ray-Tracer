#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Light.hpp"
#include "Intersection.hpp"

#define PI 3.14159265359f


void createReflectionRay(Ray *ray, const Intersection &intersection, const glm::vec3 norm);

void createRefractionRay(Ray *ray, const float n1, const float n2, const Ray &in_ray, const glm::vec3 p, const glm::vec3 n);

glm::vec3 BRDF(std::vector<GeoObject *>, std::vector<Light *>, Ray &, const int, int);

glm::vec3 BlinnPhong(Light *, Intersection &, glm::vec3);

glm::vec3 CookTorrance(Light *, Intersection &, glm::vec3);

#endif
