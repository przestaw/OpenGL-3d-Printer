#pragma once

#include "GraphicsObj.h"

class Terrain : public GraphicsObj
{
public:
	Terrain(GLfloat width, GLfloat height, GLuint subdivisions, GLfloat maxHeight, bool textureMappingByPrzemek);
};
