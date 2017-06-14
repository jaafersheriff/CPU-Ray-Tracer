// Loader class
// Parses .pov files and creates the various Camera, Light, and GeoObjects objects
#pragma once
#ifndef _LOADER_H_
#define _LOADER_H_

#include <fstream>   // read file input
#include <sstream>   // sstream
#include <stdlib.h>  // strtof
#include <vector> 	// vector
#include <string>    // find

#include "Scene.hpp"
#include "TextureBatch.hpp"

class Loader {
public:
   Loader(){};
   TextureBatch batch;
   // Walk through an input file creating a Scene object
   int parse(const char *file_name, Scene &scene);

private:
   // Parse through remaining object adding object properties
   void addProperties(GeoObject *, std::vector<std::string>, std::ifstream&);

   // Find all floats inside a line
   std::vector<float> findFloatsInLine(std::vector<std::string>);

   // Find all floats inside a word
   std::vector<float> findFloatsInWord(std::string word);

   // Adds color param to a finish object
   void createColor(GeoObject::Finish*, std::vector<std::string>);

   // Initializes Finish struct containing all GeoObject finish properties
   void createFinish(GeoObject::Finish*, std::vector<std::string>);

   // Initializes Textures struct in Object as well as individual textures themselves
   void createTextures(GeoObject::Textures*, std::vector<std::string>);

   // Break up the current line in a file into a vector<string>
   // Separating by white space
   std::vector<std::string> getLine(std::ifstream *file);
   std::vector<std::string> cleanseLine(std::vector<std::string>);

   // Create a Camera object given a file pointing to a camera line
   Camera* createCamera(std::vector<std::string>, std::ifstream &file);

   // Create a Light object given a file pointing to a light line
   Light*  createLight(std::vector<std::string>, std::ifstream &file);

   // Create geometric objects given a file pointing to a object line
   Sphere* createSphere(int, std::vector<std::string>, std::ifstream &file);
   Plane* createPlane(int, std::vector<std::string>, std::ifstream &file);
   Triangle* createTriangle(int, std::vector<std::string>, std::ifstream &file);
   BoxRenderable* createBox(int, std::vector<std::string>, std::ifstream &file);
};

#endif
