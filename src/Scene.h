// Scene class
// Contains Camera, all Lights, and all Objects in the scene
#ifndef _SCENE_H_
#define _SCENE_H_

#include <iostream>	// cout
#include <vector>	// vector

#include "Camera.h"
#include "Light.h"

#include "GeoObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

#include "Intersection.h"

class Scene {
public:
	Scene() {};

	void print();

	Camera *camera;
	std::vector<Light *> lights;
	std::vector<GeoObject *> objects;

   // Creates a ray from the camera's position to the pixel
   Ray createRay(const int window_width, const int window_height, const int pixel_x, const int pixel_y);

   // Creates an Intersection object provided a Ray
   Intersection findIntersection(Ray ray);

   // Creates output image 
   void render(const int window_width, const int window_height);
};

#endif
