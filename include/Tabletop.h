#pragma once

#include "BasicCube.h"
#include "BasicCylinder.h"
#include "CompositeGroup.h"
#include "ObjectGroup.h"

class Tabletop : public ObjectGroup {
public:
  Tabletop(GLfloat scale);
  virtual ~Tabletop() {}

private:
};
