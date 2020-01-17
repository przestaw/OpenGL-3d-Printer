#include "Extruder.h"

Extruder::Extruder(GLfloat scale) {
	GLfloat lenght = scale;
	GLfloat rodR = scale * 0.01;
	
	CompositeGroup blocks; //Obj of same type
	// First main blocks
	BasicCuboid handle(glm::vec3(0.01, 0.01, 0.01), rodR * 3, rodR * 18, rodR * 12);
	BasicCuboid mainBlock(glm::vec3(0.01, 0.01, 0.01), rodR * 12, rodR * 16, rodR * 5);
	mainBlock.translate(glm::vec3(-rodR*5, -rodR, -rodR * 3.5));

	blocks.addObject(handle);
	blocks.addObject(mainBlock);

	Material extrudeMat(10, Texture("res/extrude.jpg"), 0.6, Texture("res/extrude_ref.jpg"), 0.6);

	blocks.setMaterial(extrudeMat);

	this->addObject(blocks);

	BasicCylinder fan1(glm::vec3(0.1, 0.1, 0.1), rodR * 11, rodR * 6);
	BasicCylinder fan2(glm::vec3(0.1, 0.1, 0.1), rodR * 4, rodR * 7);
	BasicCylinder screwFan2(glm::vec3(0.9, 0.9, 0.9), rodR *4.5, rodR * 2);
	fan1.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	fan2.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	screwFan2.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);

	fan1.translate(glm::vec3(-rodR * 6, 0.0, rodR * 1.5));
	fan2.translate(glm::vec3(rodR * 7.5, rodR * 2.5, -rodR * 4.5));
	screwFan2.translate(glm::vec3(rodR * 7.5, rodR * 2.5, -rodR * 4.5));

	this->addObject(fan1);
	this->addObject(fan2);
	Material shine(186);
	screwFan2.setMaterial(shine);
	this->addObject(screwFan2);

	CompositeGroup rods; //Obj of same type
	// Second rod keepers
	BasicCylinder rod(glm::vec3(0.8, 0.8, 0.8), rodR*14.5, rodR*1.3);
	rod.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	rod.translate(glm::vec3(0.0, 0.0, rodR * 7.5));
	rods.addObject(rod);

	rod.translate(glm::vec3(0.0, 0.0, -rodR * 15));
	rods.addObject(rod);

	rods.setMaterial(shine);

	this->addObject(rods);

	CompositeGroup neadle; //Obj of same type
	// Third extrede-end
	BasicCone end(glm::vec3(0.9, 0.7, 0.7), rodR * 2, rodR * 0.05, rodR * 2);
	BasicCuboid plate(glm::vec3(0.9, 0.7, 0.7), rodR*4, rodR, rodR*4);
	
	plate.translate(glm::vec3(-rodR * 5, -rodR * 9.5, -rodR * 3.5));
	end.translate(glm::vec3(-rodR * 5, -rodR * 11, -rodR * 3.5));

	Material neadleMat(256, Texture("res/thread_ref.jpg"), 0.3, Texture("res/white.jpg"), 0.4);

	neadle.addObject(plate);
	neadle.addObject(end);

	neadle.setMaterial(neadleMat);

	this->addObject(neadle);
}