#ifndef _GEOOBJECT_H_
#define _GEOOBJECT_H_

#include <iostream>	// cout

#include <glm/glm.hpp>	// vec3

#include "Ray.hpp"

class GeoObject {
public:
	GeoObject() {
      this->translate = glm::vec3(0, 0, 0);
      this->color = glm::vec3(0, 0, 0);
      this->ambient = 0;
      this->diffuse = 0;
      this->specular = 0;
      this->shininess = 0;
      this->roughness = 0;
   };

	std::string type;

   glm::vec3 translate;
   glm::vec3 color;
   float ambient;
   float diffuse;
   float specular;
   float roughness;
   float shininess;
   
	virtual void print() = 0;
	virtual float intersect(const Ray &) = 0;
   virtual glm::vec3 findNormal(const glm::vec3 intersection_point) = 0;
};

#endif
