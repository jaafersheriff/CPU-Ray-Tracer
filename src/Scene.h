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

class Scene {
public:
	Scene() {};

	void print();

	Camera camera;
	std::vector<Light *> lights;
	std::vector<GeoObject *> objects;
};

#endif
