#pragma once
#include "BasicCone.h"

class BasicCylinder : public BasicCone{
public:
	BasicCylinder(glm::vec3 color, GLfloat height, GLfloat radius, int nbSides = 32) : BasicCone(color, height, radius, radius, nbSides) {}
	~BasicCylinder() {}
};
