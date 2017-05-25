// Recursive BRDF class
// Recursive reflection/refraction ray calculation and color calculations
#pragma once
#ifndef _BRDF_H_
#define _BRDF_H_

#include <glm/glm.hpp>

#include "Intersection.hpp"
#include "Scene.hpp"

#define PI 3.14159265359f

class BRDF {
public:
	// Used for verbose printing
	struct printNode {
		std::string type;
		Intersection in;	// Object, ray, transformed ray, t, point, normal
		Ray shadow_ray;
		glm::vec3 final_color;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 refraction_d;
		glm::vec3 reflection_d;
		float local_con;
		float refr_con;
		float refl_con;
		printNode *refr = nullptr;
		printNode *refl = nullptr;
	};

	// 0 - No ray printing
	// 1 - Ray printing
	int verbose_flag;

	// 0 - Blinn-Phong
	// 1 - Cook-Torrance
	int render_flag;

	// 0 - no fresnel calculations
	// 1 - fresnel calculations
	int fresnel_flag;

	BRDF() {
		render_flag = 0;
		verbose_flag = 0;
		fresnel_flag = 0;
	};

	// Master recursive function for tracing rays
	glm::vec3 raytrace(Scene &, Ray &, int, printNode*);
	glm::vec3 calculateColor(Scene &, Intersection &, int, printNode*);

	// Color calculation functions
	float calculateFresnelReflectance(float, Intersection &);
	float fresnel(float, glm::vec3, glm::vec3);
	glm::vec3 calculateLocalColor(Scene &, Intersection &, printNode*);
	glm::vec3 calculateReflectionColor(Scene &, Intersection &, int, printNode*);
	glm::vec3 calculateRefractionColor(Scene &, Intersection &, int, printNode*);

	// Ray calculation functions
	Ray createReflectionRay(const Intersection &);
	Ray createRefractionRay(const Intersection &);

	// Shading calculations
	glm::vec3 BlinnPhong(Light *, Intersection &, printNode*);
	glm::vec3 CookTorrance(Light *, Intersection &);

	// Verbose printing
	void createParentNode(printNode*, Intersection);
	printNode* createChildNode(printNode*, int);
	void updateParentNode(printNode*, float, float, float, glm::vec3);
	void updateParentNode(printNode*, Ray &, glm::vec3, int);
};

#endif
