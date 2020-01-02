#pragma once
#include "BasicCone.h"

class BasicCylinder : public BasicCone{
public:
	//sylinder is nothing more than a cone with equally sized top and bottom
	BasicCylinder(glm::vec3 color, GLfloat height, GLfloat radius, unsigned nbSides = 32) : BasicCone(color, height, radius, radius, nbSides) {}
	virtual ~BasicCylinder() {}
};
