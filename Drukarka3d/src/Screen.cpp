#include "Screen.h"
#include "BasicCuboid.h"
#include "Digit.h"
#include "BasicCylinder.h"

Screen::Screen(GLfloat scale, GLshort number = 0)
	: screen (glm::vec3(0.2f, 0.4f, 0.9f), scale / 6, scale * 0.07, scale / 6),
	  units (scale), tens (scale), hundreds (scale)
{
	this->number = number;
	
	screen.translate(glm::vec3(0.0f, 0.01f, 0.0f));

	units.translate(glm::vec3(-0.029f + scale/24, 0.033f, scale/18));
	tens.translate(glm::vec3(0.0f, 0.033f, 0.0f));
	hundreds.translate(glm::vec3(0.029f - scale/24, 0.033f, -scale/18));
	units.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -BasicCylinder::M_PI / 2);
	tens.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -BasicCylinder::M_PI / 2);
	hundreds.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -BasicCylinder::M_PI / 2);
	units.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -BasicCylinder::M_PI / 2);
	tens.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -BasicCylinder::M_PI / 2);
	hundreds.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -BasicCylinder::M_PI / 2);
}


void Screen::setNumber(GLshort number)
{
	this->number = number <= 999 && number >= 0 ? number : 0;
}

void Screen::incrementNumber()
{
	if (number++ == 999)
		number = 0;
}

void Screen::Draw(ShaderProgram shader, const glm::mat4& parentMat)
{
	//this->containedObjects[0]->Draw(shader, parentMat * this->model);
	screen.Draw(shader, parentMat * this->model);

	GLshort hundredsDigit = number / 100;
	GLshort tensDigit = number / 10 - (hundredsDigit * 10);
	GLshort unitsDigit = number - hundredsDigit * 100 - tensDigit * 10;

	
	units.Draw(shader, parentMat * this->model, unitsDigit);
	tens.Draw(shader, parentMat * this->model, tensDigit);
	hundreds.Draw(shader, parentMat * this->model, hundredsDigit);
	/*
	this->containedObjects[1]->Draw(shader, parentMat * this->model, unitsDigit);
	this->containedObjects[2]->Draw(shader, parentMat * this->model, tensDigit);
	this->containedObjects[3]->Draw(shader, parentMat * this->model, hundredsDigit);*/

}
/*
void Screen::setUnits(Digit& units)
{
	this->units = units;
}
void Screen::setTens(Digit& units)
{
	this->tens = units;
}
void Screen::setHundreds(Digit& units)
{
	this->hundreds = units;
}*/