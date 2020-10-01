#pragma once
#include "shprogram.h"
#include <glm/glm.hpp>
#include <string>

class LightObject {
public:
  // Sets up itself on scene
  virtual void setUp(const ShaderProgram& shaderProgram) = 0;

  void setAmbientStrength(const glm::vec3& strength);
  glm::vec3 getAmbientStrength();

  void setDiffuseStrength(const glm::vec3& strength);
  glm::vec3 getDiffuseStrength();

  void setSpecularStrength(const glm::vec3& strength);
  glm::vec3 getSpecularStrength();

  void setUniformName(const std::string& name);
  std::string getUniformName();

private:
  std::string uniformName; // name of light object used in shaders
  glm::vec3 ambientStrength;
  glm::vec3 diffuseStrength;
  glm::vec3 specularStrength;
};
