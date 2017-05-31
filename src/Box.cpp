#include "Box.hpp"

Box::Box(){
  float inf = std::numeric_limits<float>::max();
  updateBox(glm::vec3(inf, inf, inf), glm::vec3(-inf, -inf, -inf));
}

Box::Box(glm::vec3 min, glm::vec3 max) {
  updateBox(min, max);
}

void Box::updateBox(glm::vec3 min, glm::vec3 max) {
  this->minCorner = min;
  this->maxCorner = max;
  this->center = (min + max) / 2.f;
}

void Box::transform(glm::mat4 &inv_M) {
  /* TODO */
  // Calculate 8 points
  // Transform 8 points
  // this->mincorner = min(8 points)
  // this->maxcorner = max(8 points)
}

float Box::intersect(const Ray &ray) {
  float tgmax =  std::numeric_limits<float>::max();
  float tgmin = -tgmax;
 
  updateT(ray, &tgmin, &tgmax, 0); // X
  updateT(ray, &tgmin, &tgmax, 1); // Y
  updateT(ray, &tgmin, &tgmax, 2); // Z

  if (tgmin < tgmax && tgmax > 0) {
    if (tgmin > 0) {
      return std::min(tgmin, tgmax);
    }
    else {
      return tgmax;
    }
  }

  return -1;
}

void Box::updateT(const Ray &ray, float *tgmin, float *tgmax, int axis) {
  float t1 = (this->minCorner[axis] - ray.position[axis]) / ray.direction[axis];
  float t2 = (this->maxCorner[axis] - ray.position[axis]) / ray.direction[axis];
  if (t1 > t2) {
    std::swap(t1, t2);
  }
  if (t1 > *tgmin) {
    *tgmin = t1;
  }
  if (t2 < *tgmax) {
    *tgmax = t2;
  }
}
