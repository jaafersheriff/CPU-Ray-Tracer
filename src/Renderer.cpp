#include "Renderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" 

using namespace glm;

vec3 Renderer::findColor(Scene &scene, const ivec2 window_size, const int pixel_x, const int pixel_y) {
	// Set default output color to be black
	vec3 out_color = vec3(0, 0, 0);

	// Find intersection from camera to object
	Ray camera_ray = scene.createCameraRay(window_size.x, window_size.y, pixel_x, pixel_y);
	Intersection camera_intersection = scene.findIntersection(camera_ray);

	if (camera_intersection.hit()) {
		out_color = camera_intersection.object->color * camera_intersection.object->ambient;

		// Calculate ray from intersection point to light position
		for (int i = 0; i < scene.lights.size(); i++) {
			Light *light = scene.lights[i];
			vec3 light_dir = normalize(light->position - camera_intersection.point);
			Ray light_ray(camera_intersection.point, light_dir);
			Intersection light_intersection = scene.findIntersection(light_ray);

			// Blinn-Phong if there are no objects blocking the light
			if (!light_intersection.hit()) {
				vec3 half = normalize(light_dir - camera_ray.direction);
				vec3 norm = camera_intersection.object->findNormal(camera_intersection.point);
				
				// Diffuse
				vec3 diffuse = camera_intersection.object->color * camera_intersection.object->diffuse * light->color;
				out_color = out_color + diffuse * max(0.f, dot(norm, light_dir));
				// Specular
				vec3 specular = camera_intersection.object->color * camera_intersection.object->specular * light->color;
				out_color = out_color + specular * pow(max(0.f, dot(half, norm)), camera_intersection.object->shininess);
			}
		}
	}

	return out_color;
}

void Renderer::render(Scene &scene, const int window_width, const int window_height) {
	const int numChannels = 3;
	const std::string fileName = "output.png";
	const ivec2 size = ivec2(window_width, window_height);

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {

			// Calculate color
			vec3 color = findColor(scene, size, x, y);

			unsigned char red   = (unsigned char) round(color.r * 255.f);
			unsigned char green = (unsigned char) round(color.g * 255.f);
			unsigned char blue  = (unsigned char) round(color.b * 255.f);

			int pixel = (size.x * numChannels) * (size.y - 1 - y) + numChannels * x;
			data[pixel + 0] = red;
			data[pixel + 1] = green;
			data[pixel + 2] = blue;
		}
	}
	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels); 
	delete[] data;
}
