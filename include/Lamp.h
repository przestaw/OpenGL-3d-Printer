#pragma once

#include "ObjectGroup.h"

class Lamp : public ObjectGroup {
public:
  Lamp(const glm::vec3 lightPosition, const Material& material);
  virtual ~Lamp();

  void Draw(ShaderProgram shaderBasic, ShaderProgram shaderLamp,
            const glm::mat4& parentMat = glm::mat4(1.0f));

private:
};