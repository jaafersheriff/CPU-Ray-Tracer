#include "Box.hpp"
#include <vector>

Box::Box(){
  float inf = std::numeric_limits<float>::max();
  updateBox(glm::vec3(inf, inf, inf), glm::vec3(inf, inf, inf));
}

Box::Box(glm::vec3 min, glm::vec3 max) {
  updateBox(min, max);
}

void Box::updateBox(glm::vec3 min, glm::vec3 max) {
  this->minCorner = min;
  this->maxCorner = max;
  this->center = (min + max) / 2.f;
}

float Box::intersect(const Ray &ray) {
  // Check for uninitialized box
  if (!this->hasBeenInit()) {
    return -1;
  }

  float tgmax =  std::numeric_limits<float>::max();
  float tgmin = -tgmax;

  for (int axis = 0; axis <= 2; axis++) {
    // If ray is parallel
    if (!ray.direction[axis] && (ray.position[axis] >= this->minCorner[axis] || ray.position[axis] < this->maxCorner[axis])) {
      return -1;
    }
    // Otherwise update tgmin and tgmax 
    updateT(ray, &tgmin, &tgmax, axis);
    }

  if (tgmin > tgmax || tgmax < 0) {
    return -1;
  }

  if (tgmin > 0) {
    return tgmin;
  }

  return tgmax;
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

bool Box::hasBeenInit() {
  return this->minCorner[0] != std::numeric_limits<float>::max();
}
