#include "Camera.hpp"

Camera::Camera() {
   this->location = glm::vec3(0, 0, 0);
   this->up = glm::vec3(0, 0, 0);
   this->right = glm::vec3(0, 0, 0);
   this->lookAt = glm::vec3(0, 0, 0);
}

void Camera::print() {
   std::cout << "Camera:" << std::endl;
   std::cout << "- Location: {";
      std::cout << location.x << " " << location.y << " " << location.z;
      std::cout << "}" << std::endl;
   std::cout << "- Up: {";
      std::cout << up.x << " " << up.y << " " << up.z;
      std::cout << "}" << std::endl;
   std::cout << "- Right: {";
      std::cout << right.x << " " << right.y << " " << right.z;
      std::cout << "}" << std::endl;
   std::cout << "- Look at: {";
      std::cout << lookAt.x << " " << lookAt.y << " " << lookAt.z;
      std::cout << "}" << std::endl;
}
