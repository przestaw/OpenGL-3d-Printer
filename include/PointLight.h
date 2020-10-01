#pragma once
#include "LightObject.h"
#include "glew.h"

class PointLight : public LightObject {
public:
  enum class LightRange {
    RANGE_7,
    RANGE_13,
    RANGE_20,
    RANGE_32,
    RANGE_50,
    RANGE_65,
    RANGE_100,
    RANGE_160,
    RANGE_200,
    RANGE_325,
    RANGE_600,
    RANGE_3250
  };

  PointLight();

  // Sets up itself on scene
  virtual void setUp(const ShaderProgram& shaderProgram);

  void setPosition(const glm::vec3& position);
  glm::vec3 getPosition();

  // Constant, linear and Quadratic parameters are responsible for how smooth
  // and how fast light will attenuate There are methods for setting it
  // manually, however it is prefered to use setLightRange method as it uses
  // predefined values taken from
  // http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
  void setLightRange(const LightRange range);

  void setConstantParameter(const GLfloat parameter);
  GLfloat getConstantParameter();

  void setLinearParameter(const GLfloat parameter);
  GLfloat getLinearParameter();

  void setQuadraticParameter(const GLfloat parameter);
  GLfloat getQuadraticParameter();

private:
  // Range tuple of three parameters (constant, linear and quadratic)
  using RangeTuple = std::tuple<GLfloat, GLfloat, GLfloat>;

  glm::vec3 position;
  GLfloat constantParameter;
  GLfloat linearParameter;
  GLfloat quadraticParameter;
};
