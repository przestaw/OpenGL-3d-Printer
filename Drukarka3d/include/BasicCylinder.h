#pragma once
#include "BasicCone.h"

class BasicCylinder : public BasicCone{
public:
	BasicCylinder(GLfloat height, GLfloat radius, int nbSides = 32) : BasicCone(height, radius, radius, nbSides) {}
	~BasicCylinder() {}
};
