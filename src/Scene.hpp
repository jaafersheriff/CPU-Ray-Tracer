// Scene class
// Contains Camera, all Lights, and all Objects in the scene

#pragma once
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

	// Scene objects
	Camera *camera;
	std::vector<Light *> lights;
	std::vector<GeoObject *> objects;

   // Creates a ray from the camera's position to a pixel
   Ray createCameraRay(const int width, const int height, const int x, const int y, const int m, const int n, const int s);

	// Calculates the color in the world at an Intersection
	glm::vec3 findColor(const glm::ivec2, const int, const int, const int, int);
	
	void print();
};

#endif
