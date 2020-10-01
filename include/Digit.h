#pragma once

#include "BasicCuboid.h"

class Digit : public AbstractObj {
public:
  Digit(GLfloat scale);
  virtual ~Digit();

  void Draw(ShaderProgram shader, const glm::mat4& parentMat) override;
  void Draw(ShaderProgram shader, const glm::mat4& parentMat, GLshort digit);

private:
  GLfloat scale;
  std::vector<BasicCuboid> segments;
};