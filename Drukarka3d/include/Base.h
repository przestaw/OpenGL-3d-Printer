#pragma once

#include "ObjectGroup.h"
#include "CompositeGroup.h"
#include "BasicCylinder.h"
#include "BasicCube.h"

class Base : public ObjectGroup {
public:
	Base(GLfloat scale);
	virtual ~Base() {}
private:

};
