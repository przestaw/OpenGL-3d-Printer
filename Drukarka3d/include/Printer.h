#pragma once

#include "ObjectGroup.h"
#include "Base.h"
#include "Tabletop.h"
#include "Arm.h"
#include "Extruder.h"

class Printer : public ObjectGroup {
public:
	Printer(GLfloat scale, unsigned maxPos = 40);

	void spawnBall(glm::vec3 color = glm::vec3(0.2f, 1.0f, 0.4f));
	void spawnCube(glm::vec3 color = glm::vec3(0.8f, 0.2f, 0.8f));
	void spawnCone(glm::vec3 color = glm::vec3(1.0f, 0.2f, 0.0f));
	void spawnCylinder(glm::vec3 color = glm::vec3(0.1f, 1.0f, 1.0f));
	void spawnIceCream(glm::vec3 color = glm::vec3(0.9f, 0.5f, 0.6f));

	void Draw(ShaderProgram shader, const glm::mat4& parentMat = glm::mat4(1.0f)) override;

	void moveExtruderX(bool up);
	void moveExtruderY(bool up);
	void moveExtruderZ(bool up);
	void setMoveDelta(GLfloat deltaTime);

private:
	inline glm::vec3 getNeadle();

	GLfloat scale;
	GLfloat ratio = 0.01f;

	// to allow moving spawned cubes, cones etc with table
	glm::mat4 spawnedModel;

	unsigned maxPos;
	GLfloat step;

	// position of extruder
	unsigned posX;
	unsigned posY;
	unsigned posZ;

	// time between frames used for smooth move
	GLfloat deltaTime;

	// Printer parts
	Arm printerArm;
	Extruder printerExtruder;
	Base printerBase;
	Tabletop printerTop;
};
