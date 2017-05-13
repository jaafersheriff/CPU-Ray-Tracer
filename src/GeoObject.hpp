#ifndef _GEOOBJECT_H_
#define _GEOOBJECT_H_

#include <iostream>	// std::cout

#include <glm/glm.hpp>	// vec3

#include "Ray.hpp"

class GeoObject {
public:
   struct Finish {
      glm::vec3 color = glm::vec3(0, 0, 0);

      float ambient    = 0;
      float diffuse    = 0;
      float specular   = 0;
      float roughness  = 0;
      float metallic   = 0;
      float reflection = 0;
      float filter     = 0;
      float ior        = 0;
   };

	GeoObject() {
      this->translate = glm::vec3(0, 0, 0);
      this->scale = glm::vec3(0, 0, 0);
      this->rotate = glm::vec3(0, 0, 0);
   };

	std::string type;

   glm::vec3 translate;
   glm::vec3 scale;
   glm::vec3 rotate;

   Finish finish;

   int id;

	virtual void print() = 0;
	virtual float intersect(const Ray &) = 0;
   virtual glm::vec3 findNormal(const glm::vec3) = 0;

   void GeoPrint() {
      std::cout << "- Color: {";
         std::cout << finish.color.x << " " << finish.color.y << " " << finish.color.z;
         std::cout << "}" << std::endl;

      std::cout << "- Material: " << std::endl;
         std::cout << "  - Ambient: ";
            std::cout << finish.ambient << std::endl;
         std::cout << "  - Diffuse: ";
            std::cout << finish.diffuse << std::endl;
         std::cout << "  - Specular: ";
            std::cout << finish.specular << std::endl;
         std::cout << "  - Roughness: ";
            std::cout << finish.roughness << std::endl;
         std::cout << "  - Metallic: ";
            std::cout << finish.metallic << std::endl;
         std::cout << "  - Reflection: ";
            std::cout << finish.reflection << std::endl;
         std::cout << "  - Filter: ";
            std::cout << finish.filter << std::endl;
         std::cout << "  - IOR: ";
            std::cout << finish.ior << std::endl;

      std::cout << "- Transform:" << std::endl;
         std::cout << "  - Translate: {";
            std::cout << translate.x << " " << translate.y << " " << translate.z;
            std::cout << "}" << std::endl;
         std::cout << "  - Scale: {";
            std::cout << scale.x << " " << scale.y << " " << scale.z;
            std::cout << "}" << std::endl;
      std::cout << "  - Rotate: {";
            std::cout << rotate.x << " " << rotate.y << " " << rotate.z;
            std::cout << "}" << std::endl;

   }
};

#endif
