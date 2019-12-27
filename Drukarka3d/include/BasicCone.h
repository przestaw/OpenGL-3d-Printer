#pragma once

#include "GraphicsObj.h"
#include <cmath>


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

	static const double M_PI;
	static const double _2pi;
};