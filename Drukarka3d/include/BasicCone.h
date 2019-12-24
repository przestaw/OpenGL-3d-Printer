#pragma once

#include "GraphicsObj.h"
#include <cmath>
#define M_PI 3.14159265358979323846
#define _2pi  (M_PI*2.0f);

class BasicCone : public GraphicsObj {
public:

	BasicCone(glm::vec3 baseColor, GLfloat height, 
		GLfloat bottomRadius, GLfloat topRadius = 0, unsigned nbSides = 32);
	~BasicCone() {}

private:
	// Dimensions
	GLfloat height;
	GLfloat bottomRadius;
	GLfloat topRadius;
	unsigned nbSides;

	std::vector<glm::vec3> vertices();

	std::vector<GLuint> triangles();

	// Helper function to make 2 triangles from square
	inline std::vector<GLuint> quadToTri(GLuint a, GLuint b, GLuint c, GLuint d) {
		return { a, b, c, c, d, a };
	}
};