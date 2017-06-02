#include "Triangle.hpp"

Triangle::Triangle() : GeoObject() {
   this->type = "Triangle";

   this->v1 = glm::vec3(0, 0, 0);
   this->v2 = glm::vec3(0, 0, 0);
   this->v3 = glm::vec3(0, 0, 0);
}

static inline float determinant(float M[3][3]) {
   // Matrix access [y][x]
   float a = M[0][0] * (M[1][1]*M[2][2]-M[1][2]*M[2][1]);
   float b = M[0][1] * (M[1][0]*M[2][2]-M[1][2]*M[2][0]);
   float c = M[0][2] * (M[1][0]*M[2][1]-M[1][1]*M[2][0]);

   return a-b+c;
}

BoundingBox* Triangle::createBox() {
   BoundingBox* box = new BoundingBox;
   box->addPoint(v1);
   box->addPoint(v2);
   box->addPoint(v3);
   box->transform(this->M);
   return box;
}

glm::vec3 Triangle::findCenter() {
   return (this->v1 + this->v2 + this->v3) / 3.f;
}

float Triangle::intersect(const Ray &ray) {
   // Alpha?
   float A[3][3] = { {v1.x-v2.x, v1.x-v3.x, ray.direction.x},
                     {v1.y-v2.y, v1.y-v3.y, ray.direction.y},
                     {v1.z-v2.z, v1.z-v3.z, ray.direction.z} };
   float detA = determinant(A);

   // Beta
   float B[3][3] = { {v1.x-ray.position.x, v1.x-v3.x, ray.direction.x},
                     {v1.y-ray.position.y, v1.y-v3.y, ray.direction.y},
                     {v1.z-ray.position.z, v1.z-v3.z, ray.direction.z} };
   float beta = determinant(B)/detA;
   if (beta < 0 || beta > 1) {
      return -1;
   }

   // Gamma
   float G[3][3] = { {v1.x-v2.x, v1.x-ray.position.x, ray.direction.x},
                     {v1.y-v2.y, v1.y-ray.position.y, ray.direction.y},
                     {v1.z-v2.z, v1.z-ray.position.z, ray.direction.z} };
   float gamma = determinant(G)/detA;
   if (gamma < 0 || gamma > 1 - beta) {
      return -1;
   }

   // t
   float T[3][3] = { {v1.x-v2.x, v1.x-v3.x, v1.x-ray.position.x},
                     {v1.y-v2.y, v1.y-v3.y, v1.y-ray.position.y},
                     {v1.z-v2.z, v1.z-v3.z, v1.z-ray.position.z} };
   float t = determinant(T)/detA;
   return t;
}

glm::vec3 Triangle::findNormal(Ray &ray, float t) {
   glm::vec3 V = v2 - v1;
   glm::vec3 W = v3 - v1;

   return normalize(glm::vec3(V.y*W.z-V.z*W.y, V.z*W.x-V.x*W.z, V.x*W.y-V.y*W.x));
}

void Triangle::print() {
   std::cout << "- Type: Triangle" << std::endl;
   std::cout << "- Corner 1: {";
      std::cout << v1.x << " " << v1.y << " " << v1.z;
      std::cout << "}" << std::endl;
   std::cout << "- Corner 2: {";
      std::cout << v2.x << " " << v2.y << " " << v2.z;
      std::cout << "}" << std::endl;
   std::cout << "- Corner 3: {";
      std::cout << v3.x << " " << v3.y << " " << v3.z;
      std::cout << "}" << std::endl;

   GeoPrint();
}
