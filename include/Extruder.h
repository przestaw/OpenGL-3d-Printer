#pragma once

#include "BasicCube.h"
#include "BasicCylinder.h"
#include "CompositeGroup.h"
#include "ObjectGroup.h"

class Extruder : public ObjectGroup {
public:
  Extruder(GLfloat scale);
  virtual ~Extruder() {}

private:
};