#pragma once

#include "BasicCube.h"
#include "BasicCylinder.h"
#include "CompositeGroup.h"
#include "ObjectGroup.h"

class Arm : public ObjectGroup {
public:
  Arm(GLfloat scale);
  virtual ~Arm() {}

private:
};