#include "Loader.hpp"

using namespace glm;
using namespace std;


vec3 Loader::createVector(const string x, const string y, const string z) {
	return vec3(strtof(x.c_str(), 0), strtof(y.c_str(), 0), strtof(z.c_str(), 0));
}

float Loader::findFloat(string word) {
   if (word.find("}") != string::npos) {
      string w = word.substr(0, word.size()-1);
      return strtof(w.c_str(), 0);
   } 

   return strtof(word.c_str(), 0);
}

Loader::Finish Loader::createFinish(vector<string> line) {
   Finish f;
   for (unsigned int i = 1; i < line.size(); i++) {
      if (line[i].find("ambient") != string::npos) {
         f.ambient = findFloat(line[i+1]);
      }
      if (line[i].find("diffuse") != string::npos) {
         f.diffuse = findFloat(line[i+1]);
      }
      if (line[i].find("specular") != string::npos) {
         f.specular = findFloat(line[i+1]);
      }
      if (line[i].find("roughness") != string::npos) {
         f.roughness = findFloat(line[i+1]);
      }
      if (line[i].find("metallic") != string::npos) {
         f.metallic = findFloat(line[i+1]);
      }
      if (line[i].find("ior") != string::npos) {
         f.ior = findFloat(line[i+1]);
      }
   }
   return f;
}

Plane* Loader::createPlane(vector<string> line, ifstream& file) {
   // Create empty Plane object pointer
   Plane *plane = new Plane;

   // Normal
   string x = line[1].substr(2, line[1].size()-2);
   string y = line[2].substr(0, line[2].size()-1);
   string z = line[3].substr(0, line[3].size()-2);
   plane->normal = normalize(createVector(x, y, z));
   // Distance
   string d = line[4];
   plane->distance = strtof(d.c_str(), 0);

   // Continue parsing/storing file components until we reach '}' line
   while(line[0].compare("}")) {
      if (!line[0].compare("pigment")) {
         x = line[3].substr(1, line[3].size()-2);
         y = line[4].substr(0, line[4].size()-1);
         z = line[5].substr(0, line[5].size()-2);
         plane->color = createVector(x, y, z);            
      }
      if (!line[0].compare("finish")) {
         Finish finish = createFinish(line);
         plane->ambient = finish.ambient;
         plane->diffuse = finish.diffuse;
         plane->specular = finish.specular;
         plane->roughness = finish.roughness;
         plane->metallic = finish.metallic;
         plane->ior = finish.ior;
      }
      line = getLine(&file);
   }
   return plane;
}

Sphere* Loader::createSphere(vector<string> line, ifstream& file) {
   // Create empty Sphere object pointer
   Sphere *sphere = new Sphere;

   // Center
   string x = line[2].substr(1, line[2].size()-2);
   string y = line[3].substr(0, line[3].size()-1);
   string z = line[4].substr(0, line[4].size()-2);
   sphere->center = createVector(x, y, z);
   // Radius
   string rad = line[5];
   sphere->radius = strtof(rad.c_str(), 0);

   // Continue parsing/storing file components until we reach '}' line
   while(line[0].compare("}")) {
      if (!line[0].compare("pigment")) {
         x = line[4].substr(1, line[4].size()-2);
         y = line[5].substr(0, line[5].size()-1);
         z = line[6].substr(0, line[6].size()-2);
         sphere->color = createVector(x, y, z);               
      }
      if (!line[0].compare("finish")) {
         Finish finish = createFinish(line);
         sphere->ambient = finish.ambient;
         sphere->diffuse = finish.diffuse;
         sphere->specular = finish.specular;
         sphere->roughness = finish.roughness;
         sphere->metallic = finish.metallic;
         sphere->ior = finish.ior;
      }
      if (!line[0].compare("translate")) {
         x = line[1].substr(1, line[1].size()-2);
         y = line[2].substr(0, line[2].size()-1);
         z = line[3].substr(0, line[3].size()-1);
         sphere->translate = createVector(x, y, z);
      }
      line = getLine(&file);
   }

   return sphere;
}

Light* Loader::createLight(vector<string> line, ifstream& file) {
   // Create empty Light object pointer
   Light *light = new Light;

   // Position
   string x = line[1].substr(2, line[1].size()-3);
   string y = line[2].substr(0, line[2].size()-1);
   string z = line[3].substr(0, line[3].size()-1);
   light->position = createVector(x, y, z);
   // Color 
   if (!line[4].compare("color")) {
      x = line[6].substr(1, line[6].size()-2);
      y = line[7].substr(0, line[7].size()-1);
      z = line[8].substr(0, line[8].size()-2);
      light->color = createVector(x, y, z);
   }
   return light;
}

Camera* Loader::createCamera(vector<string> line, ifstream& file) {
   // Create empty Camera object pointer
   Camera *camera = new Camera();

   // Continue parsing/storing file components until we reach '}' line
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
   // Create file pointer
   ifstream inFile(file_name, ios::in | ios::binary);
	if (!inFile) {
		cout << "Error opening file: " << file_name << endl;
	}
   string word;

   // Walk through file line by line 
   while(inFile) {
      // Store line as vector<string> separating by whitespace
      vector<string> line = getLine(&inFile);

      // Skip empty lines
      if (line.size() <= 0) {
         continue;
      }

      if(!line[0].compare("camera")) {
         scene.camera = createCamera(line, inFile);
      }
      else if (!line[0].compare("light_source")) {
			scene.lights.push_back(createLight(line, inFile));
      }
      else if (!line[0].compare("sphere")){
			scene.objects.push_back(createSphere(line, inFile));
      }
      else if (!line[0].compare("plane")) {
         scene.objects.push_back(createPlane(line, inFile));
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
