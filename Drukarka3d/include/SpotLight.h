#pragma once
#include "PointLight.h"

class SpotLight :
	public PointLight
{
public:
	// Sets up itself on scene
	virtual void setUp(const ShaderProgram& shaderProgram);

	// Sets direction in which spotlight shines
	void setDirection(const glm::vec3& direction);
	glm::vec3 getDirection();

	// Sets angle where light begins to darken
	void setCutOff(const GLfloat cutOff);
	GLfloat getCutOff();

	// Sets angle where light is no more
	void setOuterCutOff(const GLfloat outerCutOff);
	GLfloat getOuterCutOff();

private:
	glm::vec3 direction;

	// In order to achieve smooth transition in spotlight from light to dark two cut offs are defined. First tells
	// where light starts to darken and second where light turns to dark completely. Between these two amount of light
	// is calculated based on position of fragment between those cutoffs.
	GLfloat cutOff;
	GLfloat outerCutOff;
};

