#include "Scene.hpp"
#include "Intersection.hpp"
#include "BRDF.hpp"

using namespace glm;

vec3 Scene::findColor(const ivec2 window_size, const int pixel_x, const int pixel_y, const int BRDF_flag) {
	// Find intersection from camera to object
	Ray camera_ray = createCameraRay(window_size.x, window_size.y, pixel_x, pixel_y);
	Intersection camera_in(this, camera_ray); 

	// If no intersection from camera to object, return black
	if (!camera_in.hit()) {
		return vec3(0, 0, 0);
	}

	// Ambient 
	vec3 out_color = camera_in.object->color * camera_in.object->ambient;

	// Calculate ray from object to each light
	for (int i = 0; i < lights.size(); i++) {
		Light *light = lights[i];
		vec3 light_dir = normalize(light->position - camera_in.point);
		Ray light_ray(camera_in.point, light_dir);
		Intersection light_in(this, light_ray);		

		// If no objects are blocking incoming light, BRDF
		if (!light_in.hit() || distance(camera_in.point, light->position) < distance(camera_in.point, light_in.point)) {
			if (BRDF_flag) {
				out_color += CookTorrance(light, camera_in);
			} else {
				out_color += BlinnPhong(light, camera_in);
			}
		}
	}

	return out_color;
}

Ray Scene::createCameraRay(const int width, const int height, const int x, const int y) {
	Ray ray;

	// p0
	ray.position = camera->location;

	// direction
	float u = (x + 0.5)/width - 0.5;
	float v = (y + 0.5)/height - 0.5;
	vec3 w = normalize(vec3(camera->lookAt - camera->location));
	ray.direction = normalize(vec3(u*camera->right + v*camera->up + w));

	return ray;
}

void Scene::print() {
	// Print camera
	camera->print();
	std::cout << std::endl << "---" << std::endl;

	// Lights
	std::cout << std::endl << lights.size() << " light(s)" << std::endl;  
	for(int i = 0; i < lights.size(); i++) {
		std::cout << std::endl << "Light[" << i << "]:" << std::endl;
		lights[i]->print();
	}
	std::cout << std::endl << "---" << std::endl;

	// Print objects
	std::cout << std::endl << objects.size() << " object(s)" << std::endl;
	for(int i = 0; i < objects.size(); i++) {
		std::cout << std::endl << "Object[" << i << "]:" << std::endl;
		objects[i]->print();
	}                            
}
