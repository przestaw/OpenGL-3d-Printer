#include "Base.h"

Base::Base(GLfloat scale) {
	GLfloat lenght = scale;
	GLfloat rodR = scale * 0.01;

	CompositeGroup blocks; //objs of same material
	// Frirst : blocks
	BasicCuboid block(glm::vec3(0.8, 0.4, 0.01), rodR * 6, rodR * 16, lenght);
	BasicCuboid baseBloc(glm::vec3(0.8, 0.4, 0.01), lenght/2, rodR * 18, rodR*18);
	BasicCuboid topBlock(glm::vec3(0.8, 0.4, 0.01), rodR * 8, rodR * 10, rodR * 18);
	BasicCuboid keyboardBloc(glm::vec3(0.8, 0.4, 0.01), lenght * 0.4, rodR * 6, lenght / 5);

	baseBloc.translate(glm::vec3(0.0, 0.0, rodR * 9 + lenght / 2));
	blocks.addObject(baseBloc);

	block.translate(glm::vec3(lenght / 2, -rodR * 3, 0.0));
	blocks.addObject(block);

	block.translate(glm::vec3(-lenght, 0.0, 0.0));
	blocks.addObject(block);

	topBlock.translate(glm::vec3(rodR, lenght, rodR * 9 + lenght / 2));
	blocks.addObject(topBlock);

	keyboardBloc.translate(glm::vec3(-lenght * 0.25, lenght * 0.08, rodR * 9 + lenght / 2));
	keyboardBloc.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 4);
	blocks.addObject(keyboardBloc);

	Material plastic(26.0f, Texture("res/plastic.jpg"), 0.2f, Texture("res/plastic_ref.jpg"), 0.8f);
	blocks.setMaterial(plastic);

	this->addObject(blocks);

	CompositeGroup rods;
	// Second : Rods
	BasicCylinder rod(glm::vec3(0.6, 0.6, 0.6), lenght, rodR);
	rod.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	rod.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 2);
	
	rod.translate(glm::vec3(lenght *0.2, 0.0, -rodR*2));
	rods.addObject(rod);

	rod.translate(glm::vec3(-lenght *0.4, 0.0, 0.0));
	rods.addObject(rod);

	rod.translate(glm::vec3(lenght *0.6, 0.0, rodR * 5));
	rods.addObject(rod);

	rod.translate(glm::vec3(-lenght*0.8, 0.0, 0.0));
	rods.addObject(rod);

	rods.setTexture(Texture("res/thread.jpg"), 0.50);

	// Third : tower
	BasicCylinder towerRod(glm::vec3(0.4, 0.4, 0.4), lenght, rodR);
	
	towerRod.translate(glm::vec3(0.0, lenght / 2, rodR * 2 + lenght / 2));
	rods.addObject(towerRod);
	towerRod.translate(glm::vec3(0.0, 0.0, rodR * 14));
	rods.addObject(towerRod);
	
	Material metal1(128, Texture("res/thread.jpg"), 0.8, Texture("res/thread_ref.jpg"), 0.6);
	rods.setMaterial(metal1);

	this->addObject(rods);

	BasicCylinder threadRod(glm::vec3(0.01, 0.01, 0.01), lenght, rodR * 2);

	threadRod.translate(glm::vec3(rodR, lenght / 2, rodR * 9 + lenght / 2));
	Material metal2(32, Texture("res/thread.jpg"), 0.6, Texture("res/thread_ref.jpg"), 0.4);
	threadRod.setMaterial(metal2);

	this->addObject(threadRod);

	// Fourth : the screen
	BasicCuboid screenBloc(glm::vec3(0.2, 0.4, 0.9), lenght / 6, rodR * 6, lenght / 6);

	screenBloc.translate(glm::vec3(-lenght * 0.2, lenght * 0.14, rodR * 9 + lenght / 2));
	screenBloc.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 4);
	this->addObject(screenBloc);
}