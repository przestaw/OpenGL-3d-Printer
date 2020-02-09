#pragma once

#include "ObjectGroup.h"
#include "CompositeGroup.h"
#include "BasicCylinder.h"
#include "BasicCube.h"

class Extruder : public ObjectGroup {
public:
	Extruder(GLfloat scale);
	virtual ~Extruder() {}
private:

};