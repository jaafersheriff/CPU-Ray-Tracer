// Scene class
// Contains Camera, all Lights, and all Objects in the scene

#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <iostream>  // cout
#include <vector>    // vector

#include "BoundingBox.hpp"

#include "Camera.hpp"
#include "Light.hpp"

#include "GeoObject.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"
#include "BoxRenderable.hpp"

class Scene {
public:
   // Spatial data structure node
   struct BoxNode {
      BoundingBox boundingBox;
      std::vector<GeoObject *> objects;

      BoxNode* leftChild = nullptr;
      BoxNode* rightChild = nullptr;
   };

   // Constructor
   Scene();

   // Scene objects
   Camera *camera;
   std::vector<Light *> lights;
   // If spatial flag is not set, scene.objects contains all objects in the scene
   // If spatial flag is set, then scene.objects contains all planes and box tree contains all other objects
   std::vector<GeoObject *> objects;

   // Spatial Data Structures
   BoxNode* rootBox;
   void createNodeBoundingBox(BoxNode *);
   void createSpatialStructures(std::vector<GeoObject *>, BoxNode*, int);  // Recursively build spatial structure tree
   void sortObjects(std::vector<GeoObject *>, int);
   
   // Creates a ray from the camera's position to a pixel
   Ray createCameraRay(const int width, const int height, const int x, const int y, const int m, const int n, const int s);

   // Calculates the color in the world at an Intersection
   glm::vec3 findColor(const glm::ivec2, const int, const int, const int, int);

   void print();
};

#endif
