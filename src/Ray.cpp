#include "Ray.h"

using namespace std;
using namespace glm;

Ray::Ray() {
	this->position = vec3(0, 0, 0);
	this->direction = vec3(0, 0, 0);
}

Ray::Ray(vec3 pos, vec3 dir) {
   this->position = vec3(pos);
   this->direction = vec3(dir);
}

vec3 Ray::intersection_point(float t) {
	return position + t * direction;
}

void Ray::print() {
   cout << "Ray: {" << position.x << " " << position.y << " " << position.z;
   cout << "} -> {" << direction.x << " " << direction.y << " " << direction.z;
   cout << "}" << endl;
}
