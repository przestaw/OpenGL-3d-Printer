#pragma once

#include "GraphicsObj.h"
#include <cmath>

class BasicSphere : public GraphicsObj {
public:
  BasicSphere(glm::vec3 baseColor, GLfloat radius, GLuint nLongitudes = 32,
              GLuint nLatitudes = 32);

private:
  static const double PI;
  static const double C2PI;

  glm::vec3 baseColor;
  GLfloat radius;
  GLuint nLongitudes; // Number of longitude lines
  GLuint nLatitudes;  // Number of latitude lines
};