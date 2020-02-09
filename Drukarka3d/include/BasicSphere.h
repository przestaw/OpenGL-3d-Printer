#pragma once

#include "GraphicsObj.h"
#include <cmath>

class BasicSphere : public GraphicsObj
{
public:
	BasicSphere(glm::vec3 baseColor, GLfloat radius, GLuint nLongitudes = 32, GLuint nLatitudes = 32);

private:
	static const double M_PI;
	static const double _2pi;

	glm::vec3 baseColor;
	GLfloat radius;
	GLuint nLongitudes;		// Number of longitude lines 
	GLuint nLatitudes;		// Number of latitude lines
};