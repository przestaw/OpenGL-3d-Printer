#include "Screen.h"
#include "BasicCuboid.h"
#include "Digit.h"

const double Screen::M_PI = 3.14159265358979323846;

Screen::Screen(GLfloat scale, GLshort number = 0)
	: screen (glm::vec3(0.2f, 0.4f, 0.9f), scale / 6, scale * 0.07, scale / 6),
	  units (scale), tens (scale), hundreds (scale)
{
	this->number = number;
	
	screen.translate(glm::vec3(0.0f, 0.01f, 0.0f));

	units.translate(glm::vec3(-0.029f + scale/24, 0.033f, scale/18));
	tens.translate(glm::vec3(0.0f, 0.033f, 0.0f));
	hundreds.translate(glm::vec3(0.029f - scale/24, 0.033f, -scale/18));
	units.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI / 2);
	tens.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI / 2);
	hundreds.rotate(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI / 2);
	units.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -M_PI / 2);
	tens.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -M_PI / 2);
	hundreds.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -M_PI / 2);
}

Screen::~Screen()
{}

void Screen::setNumber(GLshort number)
{
	this->number = number <= 999 && number >= 0 ? number : 0;
}

void Screen::incrementNumber()
{
	if (number++ == 999)
	{
		number = 0;
	}
}

void Screen::Draw(ShaderProgram shader, const glm::mat4& parentMat)
{
	screen.Draw(shader, parentMat * this->model);

	GLshort hundredsDigit = number / 100;
	GLshort tensDigit = number / 10 - (hundredsDigit * 10);
	GLshort unitsDigit = number - hundredsDigit * 100 - tensDigit * 10;

	units.Draw(shader, parentMat * this->model, unitsDigit);
	tens.Draw(shader, parentMat * this->model, tensDigit);
	hundreds.Draw(shader, parentMat * this->model, hundredsDigit);
}