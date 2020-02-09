#include "Lamp.h"
#include "Material.h"
#include "BasicCylinder.h"
#include "BasicCone.h"

Lamp::Lamp(const glm::vec3 lightPosition, const Material& material) 
{
	BasicCylinder cylinder = BasicCylinder(glm::vec3(1.0f, 1.0f, 1.0f), .4f, .1f);
	cylinder.translate(lightPosition);
	this->addObject(cylinder);

	BasicCylinder stick = BasicCylinder(glm::vec3(0.7f, 0.1f, 0.2f), 1.5f, 0.02f);
	stick.translate(lightPosition);
	stick.translate(glm::vec3(0.0f, -0.75f, 0.0f));
	stick.setMaterial(material);
	this->addObject(stick);

	BasicCone bottomCone = BasicCone(glm::vec3(0.7f, 0.1f, 0.2f), 0.06f, 0.1f, 0.15f, 32);
	bottomCone.translate(lightPosition);
	bottomCone.translate(glm::vec3(0.0f, -0.2f, 0.0f));
	bottomCone.setMaterial(material);
	this->addObject(bottomCone);
	BasicCone topCone = BasicCone(glm::vec3(0.7f, 0.1f, 0.2f), 0.06f, 0.15f, 0.1f, 32);
	topCone.translate(lightPosition);
	topCone.translate(glm::vec3(0.0f, 0.2f, 0.0f));
	topCone.setMaterial(material);
	this->addObject(topCone);
}

Lamp::~Lamp()
{}

void Lamp::Draw (ShaderProgram shaderBasic, ShaderProgram shaderLamp, const glm::mat4& parentMat) 
{
	shaderLamp.Use();
	this->containedObjects[0]->Draw(shaderLamp, (parentMat * this->model));

	shaderBasic.Use();
	for (GLuint i = 1; i < 4; ++i) 
	{
		this->containedObjects[i]->Draw(shaderBasic, (parentMat * this->model));
	}
}
