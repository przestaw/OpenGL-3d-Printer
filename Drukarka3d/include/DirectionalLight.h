#pragma once
#include "LightObject.h"

// Directional light is a light which shines in one, defined direction
// It is static and not affected by the distance from object as it has no position in world space
// It is used to simulate sunlight

class DirectionalLight :
	public LightObject
{
public:
	// Sets up itself on scene
	virtual void setUp(const ShaderProgram& shaderProgram);

	void setDirection(const glm::vec3& direction);
	glm::vec3 getDirection();

private:
	glm::vec3 direction;
};

