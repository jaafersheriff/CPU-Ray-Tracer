#include "Loader.hpp"

using namespace glm;
using namespace std;

void Loader::createColor(GeoObject::Finish *f, vector<string> line) {
   vector<float> floats;
   for (unsigned int i = 1; i < line.size(); i++) {
      if (line[i].find("rgb") != string::npos) {
         floats = findFloatsInLine(line);
         f->color.r= floats[0];
         f->color.g = floats[1];
         f->color.b = floats[2];
         if (floats.size() > 3) {
            f->filter = floats[3];
         }
      }
   }
}


void Loader::createFinish(GeoObject::Finish *f, vector<string> line) {
   for (unsigned int i = 1; i < line.size(); i++) {
      if (line[i].find("ambient") != string::npos) {
         f->ambient = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("diffuse") != string::npos) {
         f->diffuse = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("specular") != string::npos) {
         f->specular = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("roughness") != string::npos) {
         f->roughness = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("metallic") != string::npos) {
         f->metallic = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("reflection") != string::npos) {
         f->reflection = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("refraction") != string::npos) {
         f->refraction = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("ior") != string::npos) {
         f->ior = findFloatsInWord(line[i+1])[0];
      }
   }
}

Plane* Loader::createPlane(vector<string> line, ifstream& file) {
   // Create empty Plane object pointer
   Plane *plane = new Plane;

   vector<float> floats;

   // Normal
   floats = findFloatsInLine(line);
   plane->normal = normalize(vec3(floats[0], floats[1], floats[2]));
   // Distance
   plane->distance = floats[3];

   // Continue parsing/storing file components until we reach '}' line
   while(line[0].compare("}")) {
      if (!line[0].compare("pigment")) {
         createColor(&plane->finish, line);
      }
      if (!line[0].compare("finish") ) {
         createFinish(&plane->finish, line);
      }
      if (line[line.size() - 1].find("}}") != string::npos) {
         break;
      }
      line = getLine(&file);
   }
   return plane;
}

Sphere* Loader::createSphere(vector<string> line, ifstream& file) {
   // Create empty Sphere object pointer
   Sphere *sphere = new Sphere;

   vector<float> floats;

   // Center
   floats = findFloatsInLine(line);
   sphere->center = vec3(floats[0], floats[1], floats[2]);
   // Radius
   sphere->radius = floats[3];

   // Continue parsing/storing file components until we reach '}' line
   while(line[0].compare("}")) {
      if (!line[0].compare("pigment")) {
         createColor(&sphere->finish, line);
      }
      if (!line[0].compare("finish")) {
         createFinish(&sphere->finish, line);
      }
      if (!line[0].compare("translate")) {
         floats = findFloatsInLine(line);
         sphere->translate = vec3(floats[0], floats[1], floats[2]);
      }
      if (line[line.size() - 1].find("}}") != string::npos) {
         break;
      }

      line = getLine(&file);
   }

   return sphere;
}

Light* Loader::createLight(vector<string> line, ifstream& file) {
   // Create empty Light object pointer
   Light *light = new Light;

   vector<float> floats;

   // Position
   floats = findFloatsInLine(line);
   light->position = vec3(floats[0], floats[1], floats[2]);
   // Color
   light->color = vec3(floats[3], floats[4], floats[5]);

   return light;
}

Camera* Loader::createCamera(vector<string> line, ifstream& file) {
   // Create empty Camera object pointer
   Camera *camera = new Camera();

   vector<float> floats;

   // Continue parsing/storing file components until we reach '}' line
   while(line[0].compare("}")) {
      if (!line[0].compare("location")) {
         floats = findFloatsInLine(line);
         camera->location = vec3(floats[0], floats[1], floats[2]);
      }
      if (!line[0].compare("up")) {
         floats = findFloatsInLine(line);
         camera->up = vec3(floats[0], floats[1], floats[2]);
      }
      if (!line[0].compare("right")) {
         floats = findFloatsInLine(line);
         camera->right = vec3(floats[0], floats[1], floats[2]);
      }
      if (!line[0].compare("look_at")) {
         floats = findFloatsInLine(line);
         camera->lookAt = vec3(floats[0], floats[1], floats[2]);
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

vector<float> Loader::findFloatsInLine(vector<string> line) {
   vector<float> ret;

   for(string word : line) {
      vector<float> wordFloats = findFloatsInWord(word);
      ret.insert(ret.end(), wordFloats.begin(), wordFloats.end());
   }
   return ret;
}

vector<float> Loader::findFloatsInWord(string word) {
   vector<float> ret;

   // Loop through every char in string
   unsigned int w = 0;
   while(w < word.size()) {
      char c = word[w++];
      char num[256];
      int n = 0;

      // If number is found
      while ((c >= '0' && c <= '9') || c == '.' || c == '-') {
         // Continue looping through string collecting digits
         num[n++] = c;
         c = word[w++];
      }
      // If a number was created, add it to the return
      if (n > 0) {
         num[n] = '\0';
         ret.push_back(strtof(num, 0));
      }
   }

   return ret;
}
