#ifndef _LOADER_H_
#define _LOADER_H_

#include <fstream>   // read file input
#include <sstream>   // sstream 
#include <stdlib.h>  // strtof
#include <vector> 	// vector

#include "Scene.h"

class Loader {
public:
	Loader(){};

	glm::vec3 createVector(const std::string, const std::string, const std::string);
	void parse(const char *file_name, Scene &scene);
private:
	std::vector<std::string> getLine(std::ifstream *file);
   Camera* createCamera(std::vector<std::string>, std::ifstream &file);
   Light*  createLight(std::vector<std::string>, std::ifstream &file);
   Sphere* createSphere(std::vector<std::string>, std::ifstream &file);
   Plane*  createPlane(std::vector<std::string>, std::ifstream &file);
};

#endif
