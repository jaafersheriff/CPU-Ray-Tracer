#include "Loader.h"

using namespace std;

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
         // location
         line = getLine(&inFile);
         string x = line[1].substr(1, line[1].size()-2);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-1);
         scene.camera.location = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         // up
         line = getLine(&inFile);
         x = line[1].substr(1, line[1].size()-2);
         y = line[2].substr(0, line[2].size()-1);
         z = line[3].substr(0, line[3].size()-1);
         scene.camera.up = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         // right
         line = getLine(&inFile);
         x = line[1].substr(1, line[1].size()-2);
         y = line[2].substr(0, line[2].size()-1);
         z = line[3].substr(0, line[3].size()-1);
         scene.camera.right = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         // look_at
         line = getLine(&inFile);
         x = line[1].substr(1, line[1].size()-2);
         y = line[2].substr(0, line[2].size()-1);
         z = line[3].substr(0, line[3].size()-1);
         scene.camera.lookAt = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
      }
      else if (!line[0].compare("light_source")) {
			Light *light = new Light;
         // position
         string x = line[1].substr(2, line[1].size()-3);
         string y = line[2].substr(0, line[2].size()-1);
         string z = line[3].substr(0, line[3].size()-1);
         light->position = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         // color
         x = line[6].substr(1, line[6].size()-2);
         y = line[7].substr(0, line[7].size()-1);
         z = line[8].substr(0, line[8].size()-2);
         light->color = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
			scene.lights.push_back(light);
      }
      else if (!line[0].compare("sphere")){
         Sphere *sphere = new Sphere;
         // center, radius
         string x = line[2].substr(1, line[2].size()-2);
         string y = line[3].substr(0, line[3].size()-1);
         string z = line[4].substr(0, line[4].size()-2);
         string rad = line[5];
         sphere->center = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         sphere->radius = strtof(rad.c_str(), 0);
         // pigment
         line = getLine(&inFile);
         x = line[4].substr(1, line[4].size()-2);
         y = line[5].substr(0, line[5].size()-1);
         z = line[6].substr(0, line[6].size()-2);
         sphere->pigment = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
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
         	sphere->translate = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
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
         plane->normal = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         plane->distance = strtof(d.c_str(), 0);
         // pigment
         line = getLine(&inFile);
         x = line[3].substr(1, line[3].size()-2);
         y = line[4].substr(0, line[4].size()-1);
         z = line[5].substr(0, line[5].size()-2);
         plane->pigment = glm::vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
         // finish
         line = getLine(&inFile);
         x = line[2];
         y = line[4];
         plane->ambient = strtof(x.c_str(), 0);
         plane->diffuse = strtof(y.c_str(), 0);
         scene.objects.push_back(plane);
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
