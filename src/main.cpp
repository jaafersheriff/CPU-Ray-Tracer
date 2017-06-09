#include <iostream>	// std::std::cout
#include <string.h>	// strcpy
#include <vector>		// vectors
#include <iomanip>	//set precision

#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Intersection.hpp"
#include "Loader.hpp"
#include "Scene.hpp"

Renderer renderer;
Loader loader;
Scene scene;

/* Flags for different arguments
 0 - render
 1 - sceneinfo
 2 - pixelray
 3 - firsthit | pixelcolor
*/
int arg_flags[4] = {0};

int main(int args, char **argv) {

	// Catch empty line args
	if (args == 1) {
		return 1;
	}

	// Store command line arguments
	arg_flags[0] = !strcmp(argv[1], "render");
	arg_flags[1] = !strcmp(argv[1], "sceneinfo");
	arg_flags[2] = !strcmp(argv[1], "pixelray");
	arg_flags[3] = !strcmp(argv[1], "firsthit") || !strcmp(argv[1], "pixelcolor");
	if (!strcmp(argv[1], "pixeltrace")) {
		renderer.setVerbose(1);
	}
	if (!strcmp(argv[1], "printrays")) {
		renderer.setVerbose(2);
	}
	// Optional flags
	for (int i = 0; i < args; i++) {
		if (argv[i][0] == '-') {
			// Cook-Torrance
			if (std::string(argv[i]).find("altbrdf") != std::string::npos) {
				renderer.setRenderFlag(1);
			}
			// SuperSampling
			if (std::string(argv[i]).find("ss") != std::string::npos) {
				if (char *num = (strchr(argv[i], '=') + 1)) {
					renderer.setSSCount(atoi(num));
				}
			}
			// Global illumination
			if (std::string(argv[i]).find("gi") != std::string::npos) {
				renderer.setGIFlag(1);
				if (std::string(argv[i]).find("gi_samples") != std::string::npos) {
					if (char *num = (strchr(argv[i], '=') + 1)) {
						renderer.setGISamples(atoi(num));
					}					
				}
				else if (std::string(argv[i]).find("gi_bounces") != std::string::npos) {
					if (char *num = (strchr(argv[i], '=') + 1)) {
						renderer.setGIBounces(atoi(num));
					}
				}
				else if (std::string(argv[i]).find("gi_ratio") != std::string::npos) {
					if (char *num = (strchr(argv[i], '=') + 1)) {
						renderer.setGIRatio(atoi(num));
					}	
				}
			}
			// Fresnel
			if (std::string(argv[i]).find("fresnel") != std::string::npos) {
				renderer.setFresnelFlag(1);
			}
			// Spatial data structures
			if (std::string(argv[i]).find("sds") != std::string::npos) {
				renderer.setSpatialFlag(1);
			}
			// Percent printing
			if (std::string(argv[i]).find("percent") != std::string::npos) {
				renderer.setPercentFlag(1);
			}
			// Custom output file name
			if (std::string(argv[i]).find("out") != std::string::npos) {
				if (char *name = (strchr(argv[i], '=') + 1)) {
					renderer.setOutputName(name);
				}
			}
		}
	}

	std::cout << std::setprecision(4);

	// Parse file + create scene
	loader.parse(argv[2], scene);
	if (renderer.brdf.spatial_flag) {
		// Split objects into planes and other
		std::vector<GeoObject *> planes;
		std::vector<GeoObject *> other;
		for (unsigned int i = 0; i < scene.objects.size(); i++) {
			if (!strcmp(scene.objects[i]->type.c_str(), "Plane")) {
				planes.push_back(scene.objects[i]);
			}
			else {
				other.push_back(scene.objects[i]);
			}
		}
		scene.objects = planes;
		scene.createSpatialStructures(other, scene.rootBox, 0);
	}

	// Render
	if (arg_flags[0]) {
		int window_width = atoi(argv[3]);
		int window_height = atoi(argv[4]);
		renderer.render(scene, window_width, window_height);
	}

	// Sceneinfo
	if (arg_flags[1]) {
		scene.print();
	}

	if (arg_flags[2] || arg_flags[3] || renderer.brdf.verbose_flag) {
		int window_width = atoi(argv[3]);
		int window_height = atoi(argv[4]);
		int pixel_x = atoi(argv[5]);
		int pixel_y = atoi(argv[6]);
		Ray ray = scene.createCameraRay(window_width, window_height, pixel_x, pixel_y, 1, 1, 1);
		Intersection in(scene, ray, renderer.brdf.spatial_flag);
		std::cout << "Pixel: [" << pixel_x << ", " << pixel_y << "] ";
	if (arg_flags[2] || arg_flags[3]) {
		std::cout << "Ray: ";
		ray.print();
	}
	if (arg_flags[3] || renderer.brdf.verbose_flag) {
		if (arg_flags[3]) {
			in.print();
			renderer.print();
		}
		const glm::ivec2 size = glm::ivec2(window_width, window_height);
		glm::vec3 color = renderer.calculateColor(scene, size, pixel_x, pixel_y);
		std::cout << "Color: (" << color.x << ", " << color.y  << ", " << color.z << ")" << std::endl;
		if (renderer.brdf.verbose_flag == 1) {
			renderer.pixeltrace(renderer.root, 0);
		}
		if (renderer.brdf.verbose_flag == 2) {
			std::cout << "----" << std::endl;
			renderer.printrays(renderer.root, 0);
		}
	}
}

return 0;
}
