#include "Material.h"

Material::Material(const GLfloat shininess)
	: shininess(shininess)
{
}

Material::Material(const Texture& texture, const GLfloat impact, GLfloat shininess)
	: shininess(shininess),
	  diffuseMap(texture),
	  specularMap(texture),
	  diffuseImpact(impact),
	  specularImpact(impact)
{
}

Material::Material(const GLfloat shininess, 
				   const Texture& diffuseMap, const GLfloat diffuseImpact, 
				   const Texture& specularMap, const GLfloat specularImpact)
	: shininess(shininess),
	  diffuseMap(diffuseMap),
	  diffuseImpact(diffuseImpact),
	  specularMap(specularMap),
	  specularImpact(specularImpact)
{
}

Material::Material(const Material& other)
{
	this->diffuseMap = other.diffuseMap;
	this->diffuseImpact = other.diffuseImpact;
	this->specularMap = other.specularMap;
	this->specularImpact = other.specularImpact;
	this->shininess = other.shininess;
}

void Material::draw(const ShaderProgram& shader)
{
	shader.setFloatUniform("material.diffuseImpact", diffuseImpact);
	shader.setFloatUniform("material.specularImpact", specularImpact);
	shader.setFloatUniform("material.shininess", shininess);

	// Choose light maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap.getId());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap.getId());
}

Texture Material::getDiffuseMap()
{
	return diffuseMap;
}

void Material::setDiffuseMap(const Texture& map, const GLfloat impact)
{
	diffuseMap = map;
	diffuseImpact = impact;
}

Texture Material::getSpecularMap()
{
	return specularMap;
}

void Material::setSpecularMap(const Texture& map, const GLfloat impact)
{
	specularMap = map;
	specularImpact = impact;
}

GLfloat Material::getShininess()
{
	return shininess;
}

void Material::setShininess(const GLfloat shininess)
{
	this->shininess = shininess;
}
