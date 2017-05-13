#include "Loader.hpp"

void Loader::createColor(GeoObject::Finish *f, std::vector<std::string> line) {
   std::vector<float> floats;
   for (unsigned int i = 1; i < line.size(); i++) {
      if (line[i].find("rgb") != std::string::npos) {
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

void Loader::createFinish(GeoObject::Finish *f, std::vector<std::string> line) {
   for (unsigned int i = 1; i < line.size(); i++) {
      if (line[i].find("ambient") != std::string::npos) {
         f->ambient = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("diffuse") != std::string::npos) {
         f->diffuse = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("specular") != std::string::npos) {
         f->specular = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("roughness") != std::string::npos) {
         f->roughness = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("metallic") != std::string::npos) {
         f->metallic = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("reflection") != std::string::npos) {
         f->reflection = findFloatsInWord(line[i+1])[0];
      }
      if (line[i].find("ior") != std::string::npos) {
         f->ior = findFloatsInWord(line[i+1])[0];
      }
   }
}

Triangle* Loader::createTriangle(std::vector<std::string> line, std::ifstream& file) {
   // Create empty triangle object
   Triangle *triangle = new Triangle;
   std::vector<float> floats;

   // v1
   line = getLine(&file);
   floats = findFloatsInLine(line);
   triangle->v1 = glm::vec3(floats[0], floats[1], floats[2]);
   // v2
   line = getLine(&file);
   floats = findFloatsInLine(line);
   triangle->v2 = glm::vec3(floats[0], floats[1], floats[2]);
   // v3
   line = getLine(&file);
   floats = findFloatsInLine(line);
   triangle->v3 = glm::vec3(floats[0], floats[1], floats[2]);

   // Continue parsing/storing file components until we reach '}' line
   // TODO: functional programming
   while(line[0].compare("}")) {
      if (!line[0].compare("pigment")) {
         createColor(&triangle->finish, line);
      }
      if (!line[0].compare("finish") ) {
         createFinish(&triangle->finish, line);
      }
      if (line[line.size() - 1].find("}}") != std::string::npos) {
         break;
      }
      line = getLine(&file);
   }
   return triangle;
}

Plane* Loader::createPlane(std::vector<std::string> line, std::ifstream& file) {
   // Create empty Plane object pointer
   Plane *plane = new Plane;

   std::vector<float> floats;

   // Normal
   floats = findFloatsInLine(line);
   plane->normal = normalize(glm::vec3(floats[0], floats[1], floats[2]));
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
      if (line[line.size() - 1].find("}}") != std::string::npos) {
         break;
      }
      line = getLine(&file);
   }
   return plane;
}

Sphere* Loader::createSphere(std::vector<std::string> line, std::ifstream& file) {
   // Create empty Sphere object pointer
   Sphere *sphere = new Sphere;

   std::vector<float> floats;

   // Center
   floats = findFloatsInLine(line);
   sphere->center = glm::vec3(floats[0], floats[1], floats[2]);
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
         sphere->translate = glm::vec3(floats[0], floats[1], floats[2]);
      }
      if (line[line.size() - 1].find("}}") != std::string::npos) {
         break;
      }

      line = getLine(&file);
   }

   return sphere;
}

Light* Loader::createLight(std::vector<std::string> line, std::ifstream& file) {
   // Create empty Light object pointer
   Light *light = new Light;

   std::vector<float> floats;

   // Position
   floats = findFloatsInLine(line);
   light->position = glm::vec3(floats[0], floats[1], floats[2]);
   // Color
   light->color = glm::vec3(floats[3], floats[4], floats[5]);

   return light;
}

Camera* Loader::createCamera(std::vector<std::string> line, std::ifstream& file) {
   // Create empty Camera object pointer
   Camera *camera = new Camera();

   std::vector<float> floats;

   // Continue parsing/storing file components until we reach '}' line
   while(line[0].compare("}")) {
      if (!line[0].compare("location")) {
         floats = findFloatsInLine(line);
         camera->location = glm::vec3(floats[0], floats[1], floats[2]);
      }
      if (!line[0].compare("up")) {
         floats = findFloatsInLine(line);
         camera->up = glm::vec3(floats[0], floats[1], floats[2]);
      }
      if (!line[0].compare("right")) {
         floats = findFloatsInLine(line);
         camera->right = glm::vec3(floats[0], floats[1], floats[2]);
      }
      if (!line[0].compare("look_at")) {
         floats = findFloatsInLine(line);
         camera->lookAt = glm::vec3(floats[0], floats[1], floats[2]);
      }
      line = getLine(&file);
   }

   return camera;
}

void Loader::parse(const char *file_name, Scene &scene) {
   // Create file pointer
   std::ifstream inFile(file_name, std::ios::in | std::ios::binary);
	if (!inFile) {
		std::cout << "Error opening file: " << file_name << std::endl;
	}
   std::string word;

   // Walk through file line by line
   while(inFile) {
      // Store line as std::vector<std::string> separating by whitespace
      std::vector<std::string> line = getLine(&inFile);

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
         Sphere *sphere = createSphere(line, inFile);
         sphere->id = scene.objects.size()+1;
			scene.objects.push_back(sphere);
      }
      else if (!line[0].compare("plane")) {
         Plane *plane = createPlane(line, inFile);
         plane->id = scene.objects.size()+1;
         scene.objects.push_back(plane);
      }
		else if (!line[0].compare("triangle")) {
         Triangle *triangle = createTriangle(line, inFile);
         triangle->id = scene.objects.size()+1;
			scene.objects.push_back(triangle);
		}
   }
   inFile.close();
}

std::vector<std::string> Loader::getLine(std::ifstream *file) {
	char line[256];
	file->getline(line, 256);
	std::stringstream sstream(line);

	std::vector<std::string> words;
	std::string word;

	while(sstream >> word) {
		words.push_back(word);
	}

	return words;
}

std::vector<float> Loader::findFloatsInLine(std::vector<std::string> line) {
   std::vector<float> ret;

   for(std::string word : line) {
      std::vector<float> wordFloats = findFloatsInWord(word);
      ret.insert(ret.end(), wordFloats.begin(), wordFloats.end());
   }
   return ret;
}

std::vector<float> Loader::findFloatsInWord(std::string word) {
   std::vector<float> ret;

   // Loop through every char in std::string
   unsigned int w = 0;
   while(w < word.size()) {
      char c = word[w++];
      char num[256];
      int n = 0;

      // If number is found
      while ((c >= '0' && c <= '9') || c == '.' || c == '-') {
         // Continue looping through std::string collecting digits
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
