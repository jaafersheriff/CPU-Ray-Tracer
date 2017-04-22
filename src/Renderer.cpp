#include "Renderer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" 

using namespace glm;

vec3 Renderer::cookTorrance(Intersection &intersection) {
	return vec3(1, 1, 1);
}

vec3 Renderer::blinnPhong(Scene &scene, Intersection &intersection, Ray &ray) {
	vec3 out_color = intersection.object->color * intersection.object->ambient;

	// Calculate ray from intersection point to light position
	for (int i = 0; i < scene.lights.size(); i++) {
		Light *light = scene.lights[i];
		vec3 light_dir = normalize(light->position - intersection.point);
		Ray light_ray(intersection.point, light_dir);
		Intersection light_intersection = scene.findIntersection(light_ray);

		// Blinn-Phong if there are no objects blocking the light
		if (!light_intersection.hit()) {
			vec3 half = normalize(light_dir - ray.direction);
			vec3 norm = intersection.object->findNormal(intersection.point);
			
			// Diffuse
			vec3 diffuse = intersection.object->color * intersection.object->diffuse * light->color;
			out_color = out_color + diffuse * max(0.f, dot(norm, light_dir));
			// Specular
			vec3 specular = intersection.object->color * intersection.object->specular * light->color;
			out_color = out_color + specular * pow(max(0.f, dot(half, norm)), intersection.object->shininess);
		}
	}
	return out_color;
}

vec3 Renderer::findColor(Scene &scene, const ivec2 window_size, const int pixel_x, const int pixel_y) {
	// Find intersection from camera to object
	Ray camera_ray = scene.createCameraRay(window_size.x, window_size.y, pixel_x, pixel_y);
	Intersection camera_intersection = scene.findIntersection(camera_ray);

	// If we intersect an object, return calculated color
	if (camera_intersection.hit()) {
		return BRDF ? cookTorrance(camera_intersection) : blinnPhong(scene, camera_intersection, camera_ray);
	}

	// If no intersection occurs, return black
	return vec3(0, 0, 0);
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
