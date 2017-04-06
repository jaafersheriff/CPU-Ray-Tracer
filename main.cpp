#include <iostream>	// std::cout
#include <stdlib.h>	// atoi
#include <sstream>	// sstream
#include <string.h>	// strcpy
#include <fstream>	// read file input
#include <vector>	// vectors

#include "Structs.h"	// All the povray objects

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
		
		if(!line[0].compare("camera")) {
			line = getLine(&inFile);
			// location
			line = getLine(&inFile);
			// up
			line = getLine(&inFile);
			// right
			line = getLine(&inFile);
			// look_at
		}
		else if (!line[0].compare("light_source")) {
			
		}
		else if (!line[0].compare("sphere")){
			// center, radius
			line = getLine(&inFile);
			// pigment
			line = getLine(&inFile);
			// finish
			line = getLine(&inFile);
			// translate
		}
		else if (!line[0].compare("plane")) {
			// normal, distane
			line = getLine(&inFile);
			// pigment
			line = getLine(&inFile);
			// finish
		}
	}
	inFile.close();


	return 0;

}
