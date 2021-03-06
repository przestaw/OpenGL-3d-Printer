#pragma once

#include "BasicCuboid.h"
#include "Digit.h"

class Screen : public AbstractObj {
public:
  Screen(GLfloat scale, GLshort number);
  virtual ~Screen();

  void Draw(ShaderProgram shader, const glm::mat4& parentMat);

  void setNumber(GLshort number);
  void incrementNumber();

  static const double PI;

private:
  GLshort number;
  BasicCuboid screen;
  Digit units;
  Digit tens;
  Digit hundreds;
};