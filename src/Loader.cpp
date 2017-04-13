#include "Loader.h"

using namespace glm;
using namespace std;

vec3 Loader::createVector(const string x, const string y, const string z) {
	return vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
}

Plane* Loader::createPlane(vector<string> line, ifstream& file) {
   // TODO
}

Sphere* Loader::createSphere(vector<string> line, ifstream& file) {
   // TODO
}

Light* Loader::createLight(vector<string> line, ifstream& file) {
   Light *light = new Light;
   // position
   string x = line[1].substr(2, line[1].size()-3);
   string y = line[2].substr(0, line[2].size()-1);
   string z = line[3].substr(0, line[3].size()-1);
   light->position = createVector(x, y, z);
   // color 
   if (!line[4].compare("color")) {
      // rgb
      if (!line[5].compare("rgb")) {
         x = line[6].substr(1, line[6].size()-2);
         y = line[7].substr(0, line[7].size()-1);
         z = line[8].substr(0, line[8].size()-2);
         light->color = createVector(x, y, z);
      }
   }
   
   return light;
}

Camera* Loader::createCamera(vector<string> line, ifstream& file) {
   Camera *camera = new Camera();
   while(line[0].compare("}")) {
      if (!line[0].compare("location")) {
         string x = line[1].substr(1, line[1].size()-2);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-1);
         camera->location = createVector(x, y, z); 
      }
      if (!line[0].compare("up")) {
         string x = line[1].substr(1, line[1].size()-2);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-1);
         camera->up = createVector(x, y, z);
      } 
      if (!line[0].compare("right")) {
         string x = line[1].substr(1, line[1].size()-2);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-1);
         camera->right = createVector(x, y, z);
      }
      if (!line[0].compare("look_at")) {
         string x = line[1].substr(1, line[1].size()-2);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-1);
         camera->lookAt = createVector(x, y, z);
      }
      line = getLine(&file);
   }
   return camera;
}

void Loader::parse(const char *file_name, Scene &scene) {
   ifstream inFile(file_name);
   string word;
   while(inFile) {
      vector<string> line = getLine(&inFile);
      if (line.size() <= 0) {
         continue;
      }
      
      // camera 
      if(!line[0].compare("camera")) {
         scene.camera = createCamera(line, inFile);
      }
      else if (!line[0].compare("light_source")) {
			scene.lights.push_back(createLight(line, inFile));
      }
      else if (!line[0].compare("sphere")){
         Sphere *sphere = new Sphere;
         // center, radius
         string x = line[2].substr(1, line[2].size()-2);
         string y = line[3].substr(0, line[3].size()-1);
         string z = line[4].substr(0, line[4].size()-2);
         string rad = line[5];
         sphere->center = createVector(x, y, z);
         sphere->radius = strtof(rad.c_str(), 0);
         // pigment
         line = getLine(&inFile);
         x = line[4].substr(1, line[4].size()-2);
         y = line[5].substr(0, line[5].size()-1);
         z = line[6].substr(0, line[6].size()-2);
         sphere->pigment = createVector(x, y, z);
         // finish
         line = getLine(&inFile);
         x = line[2];
         y = line[4].substr(0, line[4].size()-1);
         sphere->ambient = strtof(x.c_str(), 0);
         sphere->diffuse = strtof(y.c_str(), 0);
         // translate
         line = getLine(&inFile);
			if (!line[0].compare("translate")) {
         	x = line[1].substr(1, line[1].size()-2);
         	y = line[2].substr(0, line[2].size()-1);
         	z = line[3].substr(0, line[3].size()-1);
         	sphere->translate = createVector(x, y, z);
         }
			scene.objects.push_back(sphere);
      }
      else if (!line[0].compare("plane")) {
         Plane *plane = new Plane;
         // normal, distance
         string x = line[1].substr(2, line[1].size()-2);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-2);
         string d = line[4];
         plane->normal = createVector(x, y, z);
         plane->distance = strtof(d.c_str(), 0);
         // pigment
         line = getLine(&inFile);
         x = line[3].substr(1, line[3].size()-2);
         y = line[4].substr(0, line[4].size()-1);
         z = line[5].substr(0, line[5].size()-2);
         plane->pigment = createVector(x, y, z);
         // finish
         line = getLine(&inFile);
         x = line[2];
         y = line[4];
         plane->ambient = strtof(x.c_str(), 0);
         plane->diffuse = strtof(y.c_str(), 0);
         scene.objects.push_back(plane);
      }
		else if (!line[0].compare("box")) {
			// TODO
		}
		else if (!line[0].compare("cone")) {
			// TODO
		}
		else if (!line[0].compare("triangle")) {
			// TODO
		}
   }
   inFile.close();
}

vector<string> Loader::getLine(ifstream *file) {
	char line[256];
	file->getline(line, 256);
	stringstream sstream(line);

	vector<string> words;
	string word;

	while(sstream >> word) {
		words.push_back(word);
	}
	
	return words;
}
