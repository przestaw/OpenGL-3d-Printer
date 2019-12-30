#pragma once

#include "GraphicsObj.h"
#include <cmath>

class BasicSphere : public GraphicsObj
{
public:
	BasicSphere(glm::vec3 baseColor, GLfloat radius, GLuint nLongitudes, GLuint nLatitudes);

private:
	const GLfloat PI_F = 3.14159265358979f;

	glm::vec3 baseColor;
	GLfloat radius;
	GLuint nLongitudes;		// Number of longitude lines 
	GLuint nLatitudes;		// Number of latitude lines
};