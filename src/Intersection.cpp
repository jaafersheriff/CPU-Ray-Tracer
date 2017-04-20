#include "Intersection.hpp"

using namespace std;

void Intersection::print() {
   if (!hit()) {
      cout << "No Hit" << endl;
      return;
   }
   
   cout << "T = " << t << endl;
   cout << "Object Type: " << object->type << endl; 
   cout << "Color: " << object->color.x << " " << object->color.y 
   << " " << object->color.z << endl;

}
