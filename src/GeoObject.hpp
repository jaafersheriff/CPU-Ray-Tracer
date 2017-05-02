#ifndef _GEOOBJECT_H_
#define _GEOOBJECT_H_

#include <iostream>	// std::cout

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
      this->roughness = 0;
      this->metallic = 0;
      this->ior = 1;
   };

	std::string type;

   glm::vec3 translate;
   glm::vec3 color;
   float ambient;
   float diffuse;
   float specular;
   float roughness;
   float metallic;
   float ior;
   
	virtual void print() = 0;
	virtual float intersect(const Ray &) = 0;
   virtual glm::vec3 findNormal(const glm::vec3 intersection_point) = 0;

   void GeoPrint() {
      std::cout << "- Material: " << std::endl;
         std::cout << "  - Ambient: ";
            std::cout << ambient << std::endl;
         std::cout << "  - Diffuse: ";
            std::cout << diffuse << std::endl;
         std::cout << "  - Specular: ";
            std::cout << specular << std::endl;
         std::cout << "  - Roughness: ";
            std::cout << roughness << std::endl;
         std::cout << "  - Metallic: ";
            std::cout << metallic << std::endl;
         std::cout << "  - IOR: ";
            std::cout << ior << std::endl;
   }
};

#endif
