#include "Scene.h"

using namespace std;

void Scene::print() {
	// Print camera
	camera.print();

	// Lights
	cout << endl << lights.size() << " light(s)" << endl;  
	for(int i = 0; i < lights.size(); i++) {
		cout << "Light[" << i << "]:" << endl;
		lights[i]->print();
	}

	// Print objects
	cout << endl << objects.size() << " object(s)" << endl;
	for(int i = 0; i < objects.size(); i++) {
		cout << "Object[" << i << "]:" << endl;
		objects[i]->print();
	}                            

}
