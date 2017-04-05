

#include <iostream>	// std::cout
#include <stdlib.h>	// atoi
#include <string.h>	// strcpy
#include <fstream>	// read file input

#include "Structs.h"	// All the povray objects

// window dimensions
int window_width;
int window_height;

// povray input file
char file_name[256];

using namespace std;

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

	ifstream inFile (file_name);
	char line[256];
	while(inFile) {
		inFile.getline(line, 256);
		cout << line << endl;
	}
	
	inFile.close();


	return 0;

}
