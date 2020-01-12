#include "Arm.h"

Arm::Arm(GLfloat scale) {
	GLfloat lenght = scale;
	GLfloat rodR = scale * 0.01;
	GLfloat threadR = scale * 0.003;

	// First : Cylinders
	BasicCylinder rod(glm::vec3(0.4, 0.4, 0.4), lenght, rodR);
	BasicCylinder thread(glm::vec3(0.2, 0.2, 0.2), lenght, threadR);
	rod.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	thread.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);

	rod.translate(glm::vec3(0.0, 0.0, rodR * 7.5));
	thread.translate(glm::vec3(0.0, 0.0, rodR * 2));

	this->addObject(rod);
	this->addObject(thread);

	rod.translate(glm::vec3(0.0, 0.0, -rodR * 15));
	thread.translate(glm::vec3(0.0, 0.0, -rodR * 4));

	this->addObject(rod);
	this->addObject(thread);

	// Second : motor and mount
	BasicCube box(glm::vec3(0.8, 0.4, 0.01), rodR * 18);
	box.translate(glm::vec3(rodR * 7.5, 0.0, lenght / 2));
	BasicCube motor(glm::vec3(0.01, 0.01, 0.01), rodR * 12);
	motor.translate(glm::vec3(-rodR * 3, 0.0, lenght / 2));
	motor.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 4);

	this->addObject(box);
	this->addObject(motor);

	// Third : Endstop
	BasicCuboid end(glm::vec3(0.8, 0.4, 0.01), rodR * 3, rodR * 18, rodR * 10);
	end.translate(glm::vec3(0.0, 0.0, -lenght / 2));

	this->addObject(end);

	// Fourth : Screws 

	//TODO
}