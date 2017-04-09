#include <iostream>	// std::cout
#include <string.h>	// strcpy
#include <vector>	// vectors

#include "Loader.h"
#include "Scene.h"

Loader loader;
Scene scene;

int sceneInfo = 0;
int pixelRay = 0;
int firstHit = 0;

using namespace std;

int main(int args, char **argv) {

	
	sceneInfo = args == 3 && !strcmp(argv[1], "sceneinfo");
	pixelRay = args == 7 && !strcmp(argv[1], "pixelray");
	firstHit = args == 7 && !strcmp(argv[1], "firsthit");
	if (!sceneInfo && !pixelRay && !firstHit) {
		cerr << "Invalid arguments" << endl;
		return 1;
	}	

	/* Parse file, create scene */
	loader.parse(argv[2], scene);

	/* print scene info */
	if (sceneInfo)
		scene.print();

	return 0;

}
