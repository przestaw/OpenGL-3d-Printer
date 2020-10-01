#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
  // By default lights are turned off
  setAmbientStrength(glm::vec3(0.0f));
  setDiffuseStrength(glm::vec3(0.0f));
  setSpecularStrength(glm::vec3(0.0f));
}

void DirectionalLight::setUp(const ShaderProgram& shaderProgram) {
  shaderProgram.setVec3Uniform(std::string(getUniformName() + ".direction"),
                               direction);
  shaderProgram.setVec3Uniform(
      std::string(getUniformName() + ".ambientStrength"), getAmbientStrength());
  shaderProgram.setVec3Uniform(
      std::string(getUniformName() + ".diffuseStrength"), getDiffuseStrength());
  shaderProgram.setVec3Uniform(
      std::string(getUniformName() + ".specularStrength"),
      getSpecularStrength());
}

void DirectionalLight::setDirection(const glm::vec3& direction) {
  this->direction = direction;
}

glm::vec3 DirectionalLight::getDirection() { return direction; }
