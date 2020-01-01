#include "DirectionalLight.h"

void DirectionalLight::setUp(const ShaderProgram& shaderProgram)
{
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".direction"), direction);
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".ambientStrength"), getAmbientStrength());
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".diffuseStrength"), getDiffuseStrength());
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".specularStrength"), getSpecularStrength());
}

void DirectionalLight::setDirection(const glm::vec3& direction)
{
	this->direction = direction;
}

glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}
