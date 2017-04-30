#ifndef _LOADER_H_
#define _LOADER_H_

#include <fstream>   // read file input
#include <sstream>   // sstream 
#include <stdlib.h>  // strtof
#include <vector> 	// vector
#include <string>    // find

#include "Scene.hpp"

class Loader {

struct Finish {
   float ambient = 0;
   float diffuse = 0;
   float specular = 0;
   float roughness = 0;
   float metallic = 0;
   float ior = 0;
};

public:
	Loader(){};

   // Return a vec3 of three strings assuming they represent floating point values
   glm::vec3 createVector(const std::string, const std::string, const std::string);

   // Walk through an input file creating a Scene object
	void parse(const char *file_name, Scene &scene);
private:
   // Finds a float inside a string -- catches brackets { } within string
   float findFloat(std::string word);

   // Returns a Finish struct containing all GeoObject finish properties
   Finish createFinish(std::vector<std::string>);

   // Break up the current line in a file into a vector<string>
   // Separating by white space
	std::vector<std::string> getLine(std::ifstream *file);

   // Create a Camera object given a file pointing to a camera line
   Camera* createCamera(std::vector<std::string>, std::ifstream &file);

   // Create a Light object given a file pointing to a light line
   Light*  createLight(std::vector<std::string>, std::ifstream &file);

   // Create a Sphere object given a file pointing to a sphere line
   Sphere* createSphere(std::vector<std::string>, std::ifstream &file);

   // Create a Plane object given a file pointing to a plane line
   Plane*  createPlane(std::vector<std::string>, std::ifstream &file);
};

#endif
