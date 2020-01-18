#include "Printer.h"
#include <BasicSphere.h>
#include "IceCream.h"

Printer::Printer(GLfloat scale_c, unsigned maxPos_a) : 
	scale(scale_c), maxPos(maxPos_a), 
	posX(maxPos_a/2), posY(maxPos_a/2), posZ(maxPos_a/2),  
	step(0.8 * scale / maxPos),
	printerArm(scale), printerExtruder(scale), 
	printerBase(scale), printerTop(scale) {

	printerArm.translate(
		glm::vec3(0.0, (0.13 + (static_cast<GLfloat>(posZ) / maxPos)) * scale, 0.0));
	printerExtruder.translate(
		glm::vec3(0.0, (0.13 + (static_cast<GLfloat>(posZ) / maxPos)) * scale, 0.035 * scale));
}

void Printer::spawnBall(glm::vec3 color){
	BasicSphere temp(color, scale * ratio, 9, 9);
	temp.translate(getNeadle()); 
	this->addObject(std::make_unique<BasicSphere>(std::move(temp)));
	
	printerBase.incrementNumberOnScreen();
}

void Printer::spawnCube(glm::vec3 color) {
	BasicCube temp(color, scale * ratio);
	temp.translate(getNeadle()); 
	temp.setTexture(Texture("res/citrus.jpg"),0.99);
	this->addObject(std::make_unique<BasicCube>(std::move(temp)));

	printerBase.incrementNumberOnScreen();

}

void Printer::spawnCone(glm::vec3 color) {
	BasicCone temp(color,scale * ratio ,scale * ratio);
	temp.translate(getNeadle()); 
	this->addObject(std::make_unique<BasicCone>(std::move(temp)));

	printerBase.incrementNumberOnScreen();
}

void Printer::spawnCylinder(glm::vec3 color) {
	BasicCone temp(color, scale * ratio, scale * ratio);
	temp.translate(getNeadle()); 
	this->addObject(std::make_unique<BasicCone>(std::move(temp)));

	printerBase.incrementNumberOnScreen();
}

void Printer::spawnIceCream(glm::vec3 color){
	IceCream temp(scale * ratio * 3, color);
	temp.translate(getNeadle() + glm::vec3(0.0, -scale*(ratio*2.5*1.17), 0.0));
	
	this->copyObjects(temp);

	printerBase.incrementNumberOnScreen();
}

void Printer::deleteSpawned() {
	this->containedObjects.clear();
}

void Printer::Draw(ShaderProgram shader, const glm::mat4& parentMat) {
	ObjectGroup::Draw(shader, parentMat * spawnedModel);

	printerArm.Draw(shader, parentMat * model);
	printerExtruder.Draw(shader, parentMat * model);
	printerBase.Draw(shader, parentMat * model);
	printerTop.Draw(shader, parentMat * model);
}

void Printer::moveExtruderX(bool up) {
	if (up) {
		if (posX < maxPos) {
			printerTop.translate(glm::vec3(step, 0.0, 0.0));
			spawnedModel = glm::translate(spawnedModel, glm::vec3(step, 0.0, 0.0));
			posX++;
		}
	}
	else {
		if (posX > 0) {
			printerTop.translate(glm::vec3( -step, 0.0, 0.0));
			spawnedModel = glm::translate(spawnedModel, glm::vec3(- step, 0.0, 0.0));
			posX--;
		}
	}
}

void Printer::moveExtruderY(bool up) {
	if (up) {
		if (posY < maxPos) {
			printerExtruder.translate(glm::vec3(0.0, 0.0, step));
			posY++;
		}
	}
	else {
		if (posY > 0) {
			printerExtruder.translate(glm::vec3(0.0, 0.0,-step));
			posY--;
		}
	}
}

void Printer::moveExtruderZ(bool up) {
	if (up) {
		if (posZ < maxPos) {
			printerArm.translate(glm::vec3(0.0, step, 0.0));
			printerExtruder.translate(glm::vec3(0.0, step, 0.0));
			posZ++;
		}
	} else {
		if (posZ > 0) {
			printerArm.translate(glm::vec3(0.0, -step, 0.0));
			printerExtruder.translate(glm::vec3(0.0, -step, 0.0));
			posZ--;
		}
	}
}

void Printer::setMoveDelta(GLfloat deltaTime)
{
}

inline glm::vec3 Printer::getNeadle()
{
	return glm::vec3(
		(- 0.05 * scale) - (static_cast<double>(posX)* step) + 0.4 * scale,
		(static_cast<double>(posZ) * step) + 0.1 * scale,
		(static_cast<double>(posY) * step) - 0.4 * scale);
}
