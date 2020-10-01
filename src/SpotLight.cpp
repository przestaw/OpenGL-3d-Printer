#include "SpotLight.h"

SpotLight::SpotLight() : PointLight() {}

void SpotLight::setUp(const ShaderProgram& shaderProgram) {
  PointLight::setUp(shaderProgram);
  shaderProgram.setVec3Uniform(std::string(getUniformName() + ".direction"),
                               getDirection());
  shaderProgram.setFloatUniform(std::string(getUniformName() + ".cutOff"),
                                getCutOff());
  shaderProgram.setFloatUniform(std::string(getUniformName() + ".outerCutOff"),
                                getOuterCutOff());
}

void SpotLight::setDirection(const glm::vec3& direction) {
  this->direction = direction;
}

glm::vec3 SpotLight::getDirection() { return direction; }

void SpotLight::setCutOff(const GLfloat cutOff) {
  this->cutOff = glm::cos(glm::radians(cutOff));
}

GLfloat SpotLight::getCutOff() { return cutOff; }

void SpotLight::setOuterCutOff(const GLfloat outerCutOff) {
  this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}

GLfloat SpotLight::getOuterCutOff() { return outerCutOff; }
