#include <iostream>	// std::cout
#include <string.h>	// strcpy
#include <vector>	// vectors
#include <iomanip>	//set precision

#include "Loader.h"
#include "Scene.h"

Loader loader;
Scene scene;

int render = 0;
int sceneInfo = 0;
int pixelRay = 0;
int firstHit = 0;

using namespace std;

int main(int args, char **argv) {

	render = !strcmp(argv[1], "render");
	sceneInfo = !strcmp(argv[1], "sceneinfo");
	pixelRay = !strcmp(argv[1], "pixelray");
	firstHit = !strcmp(argv[1], "firsthit");
	if (!render && !sceneInfo && !pixelRay && !firstHit) {
		cerr << "Invalid arguments" << endl;
		return 1;
	}	

	/* Parse file, create scene */
	loader.parse(argv[2], scene);

	if (sceneInfo) {
		scene.print();
	}
	if (pixelRay || firstHit) {
		int window_width = atoi(argv[3]);
		int window_height = atoi(argv[4]);
		int pixel_x = atoi(argv[5]);
		int pixel_y = atoi(argv[6]);
		Ray ray = scene.createRay(window_width, window_height, pixel_x, pixel_y);
		cout << setprecision(4);
		cout << "Pixel: [" << pixel_x << ", " << pixel_y << "] ";
		ray.print();
		if (firstHit) {
			Intersection in = scene.findIntersection(ray);
			in.print();
		}
 	}
	if (render) {
		int window_width = atoi(argv[3]);
		int window_height = atoi(argv[4]);
		scene.render(window_width, window_height);
	}
	return 0;
}
