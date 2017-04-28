#include "Sphere.hpp"

using namespace glm;
using namespace std;

Sphere::Sphere() : GeoObject() {
	this->type = "Sphere";
		
	this->center = vec3(0, 0, 0);
	this->radius = 0;
}

vec3 Sphere::findNormal(const vec3 intersection_point) {
	return normalize(intersection_point - center);
}


float Sphere::intersect(const Ray &ray) {
	vec3 pc = ray.position-center;

	float A = dot(ray.direction, ray.direction);
	float B = dot(ray.direction + ray.direction, pc);
	float C = dot(pc, pc) - radius*radius;

	float det = sqrt(B*B-4*A*C);
	float t1 = (-B+det)/(2*A);
	float t2 = (-B-det)/(2*A);
	
	return t1 < t2 ? t1 : t2;
}

void Sphere::print() {
	cout << "- Type: Sphere" << endl;
	cout << "- Center: {";
		cout << center.x << " " << center.y << " " << center.z;
		cout << "}" << endl;
	cout << "- Radius: ";
		cout << radius << endl;
	cout << "- Color: {";
		cout << color.x << " " << color.y << " " << color.z;
		cout << "}" << endl;
	cout << "- Material:" << endl;
		cout << "  - Ambient: ";
			cout << ambient << endl;
		cout << "  - Diffuse: ";
			cout << diffuse << endl;
}
