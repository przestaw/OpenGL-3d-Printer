#include "PointLight.h"

#include <map>

void PointLight::setUp(const ShaderProgram& shaderProgram)
{
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".position"), getPosition());
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".ambientStrength"), getAmbientStrength());
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".diffuseStrength"), getDiffuseStrength());
	shaderProgram.setVec3Uniform(std::string(getUniformName() + ".specularStrength"), getSpecularStrength());
	shaderProgram.setFloatUniform(std::string(getUniformName() + ".constantParameter"), getConstantParameter());
	shaderProgram.setFloatUniform(std::string(getUniformName() + ".linearParameter"), getLinearParameter());
	shaderProgram.setFloatUniform(std::string(getUniformName() + ".quadraticParameter"), getQuadraticParameter());
}

void PointLight::setPosition(const glm::vec3& position)
{
	this->position = position;
}

glm::vec3 PointLight::getPosition()
{
	return position;
}

void PointLight::setLightRange(const LightRange range)
{
	static const std::map<LightRange, RangeTuple> rangeMap {
		{ LightRange::RANGE_7, RangeTuple(	1.0f,	0.7f,	1.8) },
		{ LightRange::RANGE_13, RangeTuple(	1.0f,	0.35f,	0.44) },
		{ LightRange::RANGE_20, RangeTuple(	1.0f,	0.22f,	0.20) },
		{ LightRange::RANGE_32, RangeTuple(	1.0f,	0.14f,	0.07) },
		{ LightRange::RANGE_50, RangeTuple(	1.0f,	0.09f,	0.032) },
		{ LightRange::RANGE_65, RangeTuple(	1.0f,	0.07f,	0.017) },
		{ LightRange::RANGE_100, RangeTuple(1.0f,	0.045f, 0.0075) },
		{ LightRange::RANGE_160, RangeTuple(1.0f,	0.027f, 0.0028) },
		{ LightRange::RANGE_200, RangeTuple(1.0f,	0.022f, 0.0019) },
		{ LightRange::RANGE_325, RangeTuple(1.0f,	0.014f, 0.0007) },
		{ LightRange::RANGE_600, RangeTuple(1.0f,	0.007f, 0.0002) },
		{ LightRange::RANGE_3250, RangeTuple(1.0f,	0.0014f,0.000007) }
	};

	GLfloat constantParameter, linearParameter, quadraticParameter;

	std::tie(constantParameter, linearParameter, quadraticParameter) = rangeMap.find(range)->second;
	setConstantParameter(constantParameter);
	setLinearParameter(linearParameter);
	setQuadraticParameter(quadraticParameter);
}

void PointLight::setConstantParameter(const GLfloat parameter)
{
	constantParameter = parameter;
}

GLfloat PointLight::getConstantParameter()
{
	return constantParameter;
}

void PointLight::setLinearParameter(const GLfloat parameter)
{
	linearParameter = parameter;
}

GLfloat PointLight::getLinearParameter()
{
	return linearParameter;
}

void PointLight::setQuadraticParameter(const GLfloat parameter)
{
	quadraticParameter = parameter;
}

GLfloat PointLight::getQuadraticParameter()
{
	return quadraticParameter;
}
