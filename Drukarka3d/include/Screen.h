#pragma once
#include "BasicCuboid.h"
//#include "ObjectGroup.h"
#include "Digit.h"
class Screen : public GraphicsObj
{
public:
	Screen(GLfloat scale, GLshort number);

	void Draw(ShaderProgram shader, const glm::mat4& parentMat);

	void setNumber(GLshort number);
	void incrementNumber();
private:
	GLshort number;
	BasicCuboid screen;
	Digit units;
	Digit tens;
	Digit hundreds;
};