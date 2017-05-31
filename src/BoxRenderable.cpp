#include "BoxRenderable.hpp"


BoxRenderable::BoxRenderable() : GeoObject(), Box() {

}

BoundingBox* BoxRenderable::createBox() {
   BoundingBox *box = new BoundingBox(this->minCorner, this->maxCorner);
   box->transform(this->inv_M);
   return box;
}

float BoxRenderable::intersect(const Ray &ray) {
   return Box::intersect(ray);
}

glm::vec3 BoxRenderable::findNormal(const glm::vec3 intersection_point) {
   /* TODO */
   return glm::vec3(0, 1, 0);
}

void BoxRenderable::print() {
   /* TODO */
}