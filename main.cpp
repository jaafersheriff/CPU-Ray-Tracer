#include <iostream>	// std::cout
#include <stdlib.h>	// atoi
#include <sstream>	// sstream
#include <string.h>	// strcpy
#include <fstream>	// read file input
#include <vector>	// vectors

#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

// window dimensions
int window_width;
int window_height;

// povray input file
char file_name[256];

using namespace std;

vector<string> getLine(ifstream *file) {
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

int main(int args, char **argv) {

	/* Input error handling */
	if (args != 4) {
		cerr << "Usage: ./raytrace <width> <height> <input_filename>" << endl;
		return 1;
	}

	/* Store and print args */
	window_width   = atoi(argv[1]);
	window_height = atoi(argv[2]);
	strcpy(file_name, argv[3]);
	cout << "Window width:  " << window_width << endl;
	cout << "Window height: " << window_height << endl;
	cout << "Input file:    " << file_name << endl;

	/* Parse file */

	// Set up objects
	Camera camera;
	Light light;
	vector<Sphere> spheres;
	vector<Plane>  planes;

	ifstream inFile (file_name);
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
			camera.location = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			// up
			line = getLine(&inFile);
			x = line[1].substr(1, line[1].size()-2);
			y = line[2].substr(0, line[2].size()-1);
			z = line[3].substr(0, line[3].size()-1);
			camera.up = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			// right
			line = getLine(&inFile);
			x = line[1].substr(1, line[1].size()-2);
			y = line[2].substr(0, line[2].size()-1);
			z = line[3].substr(0, line[3].size()-1);
			camera.right = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			// look_at
			line = getLine(&inFile);
			x = line[1].substr(1, line[1].size()-2);
			y = line[2].substr(0, line[2].size()-1);
			z = line[3].substr(0, line[3].size()-1);
			camera.lookAt = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
		}
		else if (!line[0].compare("light_source")) {
			// position
			string x = line[1].substr(3, line[1].size()-4);
			string y = line[2].substr(0, line[2].size()-1);
			string z = line[3].substr(0, line[3].size()-1);
			light.position = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			// color
			x = line[6].substr(1, line[6].size()-2);
			y = line[7].substr(0, line[7].size()-1);
			z = line[8].substr(0, line[8].size()-2);
			light.color = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
		}
		else if (!line[0].compare("sphere")){
			Sphere sphere;
			// center, radius
			string x = line[2].substr(1, line[2].size()-2);
			string y = line[3].substr(0, line[3].size()-1);
			string z = line[4].substr(0, line[4].size()-2);
			string rad = line[5];
			sphere.center = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			sphere.radius = atoi(rad.c_str());
			// pigment
			line = getLine(&inFile);
			x = line[4].substr(1, line[4].size()-2);
			y = line[5].substr(0, line[5].size()-1);
			z = line[6].substr(0, line[6].size()-2);
			sphere.pigment = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			// finish
			line = getLine(&inFile);
			x = line[2];
			y = line[4].substr(0, line[4].size()-1);
			sphere.ambient = atoi(x.c_str());
			sphere.diffuse = atoi(y.c_str());
			// translate
			line = getLine(&inFile);
			x = line[1].substr(1, line[1].size()-2);
			y = line[2].substr(0, line[2].size()-1);
			z = line[3].substr(0, line[3].size()-1);
			sphere.position = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			spheres.push_back(sphere);
		}
		else if (!line[0].compare("plane")) {
			Plane plane;
			// normal, distance
			string x = line[1].substr(2, line[1].size()-2);
			string y = line[2].substr(0, line[2].size()-1);
			string z = line[3].substr(0, line[3].size()-2);
			string d = line[4];
			plane.normal = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			plane.distance = atoi(d.c_str());
			// pigment
			line = getLine(&inFile);
			x = line[3].substr(1, line[3].size()-2);
			y = line[4].substr(0, line[4].size()-1);
			z = line[5].substr(0, line[5].size()-2);
			plane.pigment = glm::vec3(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()));
			// finish
			line = getLine(&inFile);
			x = line[2];
			y = line[4];
			plane.ambient = atoi(x.c_str());
			plane.diffuse = atoi(y.c_str());
			planes.push_back(plane);
		}
	}
	inFile.close();


	return 0;

}
