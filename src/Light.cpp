#include "Light.hpp"

Light::Light() {
   this->position = glm::vec3(0, 0, 0);
   this->color = glm::vec3(0, 0, 0);
}

void Light::print() {
   std::cout << "- Location: {";
      std::cout << position.x << " " << position.y << " " << position.z;
      std::cout << "}" << std::endl;
   std::cout << "- Color: {";
      std::cout << color.x << " " << color.y << " " << color.z;
      std::cout << "}" << std::endl;
}
