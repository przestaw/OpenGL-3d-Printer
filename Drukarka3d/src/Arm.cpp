#include "Arm.h"

Arm::Arm(GLfloat scale) {
	GLfloat lenght = scale;
	GLfloat rodR = scale * 0.01;
	GLfloat threadR = scale * 0.003;

	CompositeGroup rods; //Obj of same type [texture]
	CompositeGroup threads; //Obj of same type [texture]
	// First : Cylinders
	BasicCylinder rod(glm::vec3(0.4, 0.4, 0.4), lenght, rodR);
	BasicCylinder thread(glm::vec3(0.01, 0.01, 0.01), lenght, threadR);
	rod.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	thread.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);

	rod.translate(glm::vec3(0.0, 0.0, rodR * 7.5));
	thread.translate(glm::vec3(0.0, 0.0, rodR * 2));

	rods.addObject(rod);
	threads.addObject(thread);

	rod.translate(glm::vec3(0.0, 0.0, -rodR * 15));
	thread.translate(glm::vec3(0.0, 0.0, -rodR * 4));

	rods.addObject(rod);
	threads.addObject(thread);

	Material metal1(128, Texture("res/thread.jpg"), 0.8, Texture("res/thread_ref.jpg"), 0.6);
	rods.setMaterial(metal1);

	Material metal2(32, Texture("res/thread.jpg"), 0.6, Texture("res/thread_ref.jpg"), 0.4);
	threads.setMaterial(metal2);
	
	this->addObject(rods);
	this->addObject(threads);

	CompositeGroup orangeBoxes; //Obj of same type
	// Second : motor and mount
	BasicCube box(glm::vec3(0.8, 0.4, 0.01), rodR * 18);
	box.translate(glm::vec3(rodR * 7.5, 0.0, rodR * 9 + lenght / 2 ));
	BasicCube motor(glm::vec3(0.01, 0.01, 0.01), rodR * 12);
	motor.translate(glm::vec3(-rodR * 3, 0.0, rodR * 9 + lenght / 2));
	motor.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 4);

	Material darkPlastic(26.0f, Texture("res/motor.jpg"), 0.9f, Texture("res/white.jpg"), 0.5f);
	motor.setMaterial(darkPlastic);

	orangeBoxes.addObject(box);

	this->addObject(motor);
	// Third : Endstop
	BasicCuboid end(glm::vec3(0.8, 0.4, 0.01), rodR * 3, rodR * 18, rodR * 10);
	end.translate(glm::vec3(0.0, 0.0, -lenght / 2));

	orangeBoxes.addObject(end);

	Material plastic(26.0f, Texture("res/plastic.jpg"), 0.2f, Texture("res/plastic_ref.jpg"), 0.8f);
	orangeBoxes.setMaterial(plastic);

	this->addObject(orangeBoxes);

	// Fourth : Screws 
	//TODO
}