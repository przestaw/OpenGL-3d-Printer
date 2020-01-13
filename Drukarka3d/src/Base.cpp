#include "Base.h"

Base::Base(GLfloat scale) {
	GLfloat lenght = scale;
	GLfloat rodR = scale * 0.01;

	// Frirst : blocks
	BasicCuboid block(glm::vec3(0.8, 0.4, 0.01), rodR * 6, rodR * 16, lenght);
	BasicCuboid baseBloc(glm::vec3(0.8, 0.4, 0.01), lenght/2, rodR * 16, rodR*18);
	BasicCuboid topBlock(glm::vec3(0.8, 0.4, 0.01), rodR * 8, rodR * 10, rodR * 18);
	BasicCuboid keyboardBloc(glm::vec3(0.8, 0.4, 0.01), lenght * 0.4, rodR * 6, lenght / 5);

	baseBloc.translate(glm::vec3(0.0, 0.0, rodR * 9 + lenght / 2));
	this->addObject(baseBloc);

	block.translate(glm::vec3(lenght / 2, 0.0, 0.0));
	this->addObject(block);

	block.translate(glm::vec3(-lenght, 0.0, 0.0));
	this->addObject(block);

	topBlock.translate(glm::vec3(rodR, lenght, rodR * 9 + lenght / 2));
	this->addObject(topBlock);

	keyboardBloc.translate(glm::vec3(-lenght * 0.25, lenght * 0.08, rodR * 9 + lenght / 2));
	keyboardBloc.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 4);
	this->addObject(keyboardBloc);

	BasicCuboid screenBloc(glm::vec3(0.2, 0.4, 0.9), lenght / 6, rodR * 6, lenght / 6);

	screenBloc.translate(glm::vec3(-lenght * 0.2, lenght * 0.14, rodR * 9 + lenght / 2));
	screenBloc.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 4);
	this->addObject(screenBloc);	

	// Second : Rods
	BasicCylinder rod(glm::vec3(0.4, 0.4, 0.4), lenght, rodR);
	rod.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	rod.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 2);
	
	rod.translate(glm::vec3(lenght *0.2, 0.0, -rodR*2));
	this->addObject(rod);

	rod.translate(glm::vec3(-lenght *0.4, 0.0, 0.0));
	this->addObject(rod);

	rod.translate(glm::vec3(lenght *0.6, 0.0, rodR * 5));
	this->addObject(rod);

	rod.translate(glm::vec3(-lenght*0.8, 0.0, 0.0));
	this->addObject(rod);

	// Third : tower
	BasicCylinder towerRod(glm::vec3(0.4, 0.4, 0.4), lenght, rodR);
	BasicCylinder threadRod(glm::vec3(0.2, 0.2, 0.2), lenght, rodR*2);

	towerRod.translate(glm::vec3(0.0, lenght / 2, rodR * 2 + lenght / 2));
	this->addObject(towerRod); 
	towerRod.translate(glm::vec3(0.0, 0.0, rodR * 14));
	this->addObject(towerRod); 
	threadRod.translate(glm::vec3(rodR, lenght / 2, rodR * 9 + lenght /2));
	this->addObject(threadRod);

	// Fourth : the screen

	

}