#pragma once

#include "BasicCube.h"
#include "BasicCylinder.h"
#include "CompositeGroup.h"
#include "ObjectGroup.h"
#include "Screen.h"

class Base : public ObjectGroup {
public:
  Base(GLfloat scale);
  virtual ~Base() {}

  void Draw(ShaderProgram program, const glm::mat4& parentMat);

  void incrementNumberOnScreen();
  void setNumberOnScreen(short number);

private:
  Screen screen;
};
