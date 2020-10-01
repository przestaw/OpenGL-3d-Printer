#pragma once

#include "GraphicsObj.h"

/*
 * Cuboid primitive.
 */
class BasicCuboid : public GraphicsObj {
public:
  BasicCuboid(glm::vec3 baseColor, GLfloat width, GLfloat height,
              GLfloat lenght);

private:
  glm::vec3 baseColor;
  GLfloat width;
  GLfloat height;
  GLfloat lenght;
};