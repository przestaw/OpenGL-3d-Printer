#pragma once

#include "BasicCuboid.h"

class BasicCube : public BasicCuboid {
public:
  BasicCube(glm::vec3 baseColor, GLfloat dim)
      : BasicCuboid(baseColor, dim, dim, dim) {}
};