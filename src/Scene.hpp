// Scene class
// Contains Camera, all Lights, and all Objects in the scene
#ifndef _SCENE_H_
#define _SCENE_H_

#include <iostream>	// cout
#include <vector>	// vector

#include "Camera.hpp"
#include "Light.hpp"

#include "GeoObject.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"

class Scene {
public:
	Scene() {};

	void print();

	Camera *camera;
	std::vector<Light *> lights;
	std::vector<GeoObject *> objects;

   // Creates a ray from the camera's position to the pixel
   Ray createCameraRay(const int window_width, const int window_height, const int pixel_x, const int pixel_y);

	// Calculates the color in the world at an Intersection
	glm::vec3 findColor(const glm::ivec2, const int, const int, const int, int);
};

#endif
