// Recursive BRDF class
// Recursive reflection/refraction ray calculation and color calculations
#pragma once
#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Intersection.hpp"
#include "Scene.hpp"

#define PI 3.14159265359f

#define DEFAULT_SAMPLES 128
#define DEFAULT_BOUNCES 2
#define DEFAULT_RATIO   8

class BRDF {
public:
	// 0 - No ray printing
	// 1 - Ray printing
	int verbose_flag;

	// 0 - no fresnel calculations
	// 1 - fresnel calculations
	int fresnel_flag;

	// 0 - iterate through each object to find intersection
	// 1 - use spatial data structure tree
	int spatial_flag;

	// 0 - default ambient calculation
	// 1 - global illumination ambient calculation
	int gi_flag;
	int gi_samples;
	int gi_bounces;
	int gi_ratio;

	BRDF() {
		verbose_flag = 0;
		fresnel_flag = 0;
		spatial_flag = 0;
		gi_flag = 0;
		gi_samples = DEFAULT_SAMPLES;
		gi_bounces = DEFAULT_BOUNCES;
		gi_ratio   = DEFAULT_RATIO;
	};

	// Master recursive function for tracing rays
	glm::vec3 raytrace(Scene &, Ray &, int);
	glm::vec3 calculateColor(Scene &, Intersection &, int);

	// Color calculation functions
	float calculateFresnelReflectance(float, Intersection &);
	float fresnel(float, glm::vec3, glm::vec3);
	glm::vec3 calculateLocalColor(Scene &, Intersection &, int);
   glm::vec3 calculateGlobalIllumination(Scene &, Intersection &, int);
	glm::vec3 calculateReflectionColor(Scene &, Intersection &, int);
	glm::vec3 calculateRefractionColor(Scene &, Intersection &, int);

	// Shading calculations
	glm::vec3 BlinnPhong(Light *, Intersection &);
};

#endif
