#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Ray.h"

class Renderer {
public:
	Renderer();

	Ray createRay(const int window_width, const int window_height, const int pixel_x, const int pixel_y);
};

#endif
