#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Intersection.hpp"

#define PI 3.14159265359f

glm::vec3 BlinnPhong(Light *, Intersection &);

glm::vec3 CookTorrance(Light *, Intersection &);

#endif