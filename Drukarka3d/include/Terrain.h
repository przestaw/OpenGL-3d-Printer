#pragma once

#include "GraphicsObj.h"

class Terrain : public GraphicsObj
{
public:
	Terrain(GLfloat width, GLfloat height, GLuint subdivisions, GLfloat maxHeight);

private:
	GLfloat width;
	GLfloat lenght;
	GLfloat maxHeight;
	GLuint subdivisions;

	void generate();
};
