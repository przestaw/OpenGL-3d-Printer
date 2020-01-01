#include "LightObject.h"
#include "..\include\LightObject.h"

void LightObject::setAmbientStrength(const glm::vec3& strength)
{
	ambientStrength = strength;
}

glm::vec3 LightObject::getAmbientStrength()
{
	return ambientStrength;
}

void LightObject::setDiffuseStrength(const glm::vec3& strength)
{
	diffuseStrength = strength;
}

glm::vec3 LightObject::getDiffuseStrength()
{
	return diffuseStrength;
}

void LightObject::setSpecularStrength(const glm::vec3& strength)
{
	specularStrength = strength;
}

glm::vec3 LightObject::getSpecularStrength()
{
	return specularStrength;
}

void LightObject::setUniformName(const std::string& name)
{
	uniformName = name;
}

std::string LightObject::getUniformName()
{
	return uniformName;
}
