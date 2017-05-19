// Abstract geometric object class
// Includes finish struct containing all finish data
// All objets have a finish, a transformation, a type, and an ID
#pragma once
#ifndef _GEOOBJECT_H_
#define _GEOOBJECT_H_

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>	// print matrices
#include <iostream>	// std::cout

#include "Ray.hpp"

class GeoObject {
public:
   // Finish struct contains all material data
   struct Finish {
      glm::vec3 color = glm::vec3(0, 0, 0);

      float ambient = 0;
      float diffuse = 0;
      float specular = 0;
      float roughness = 0;
      float metallic = 0;
      float refraction = 0;
      float reflection = 0;
      float filter = 0;
      float ior = 0;
   };



   GeoObject() {
      inv_M = glm::mat4(1.0f);
   };

   // Abstract types
   int id;
   std::string type;

   // Material properties
   Finish finish;

   // Model matrix is stored as its inverse because we never
   // use it in its normal state
   glm::mat4 inv_M;

   // Abstract functions
   virtual void print() = 0;
   virtual float intersect(const Ray &) = 0;
   virtual glm::vec3 findNormal(const glm::vec3 intersection_point) = 0;

   // Parent print functionality
   // All objects need to print their finish and transformation
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
         std::cout << "  - Refraction: ";
            std::cout << finish.refraction << std::endl;
         std::cout << "  - Filter: ";
            std::cout << finish.filter << std::endl;
         std::cout << "  - IOR: ";
            std::cout << finish.ior << std::endl;

		std::cout << " - Model Transform: " << std::endl;
			std::cout << "  " << glm::to_string(inv_M) << std::endl;
  }
};

#endif
