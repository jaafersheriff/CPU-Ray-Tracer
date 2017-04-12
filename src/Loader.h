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
};

#endif
