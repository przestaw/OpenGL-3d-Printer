#include "Tabletop.h"

Tabletop::Tabletop(GLfloat scale) {
	GLfloat lenght = scale;
	GLfloat rodR = scale * 0.01;

	BasicCylinder rod(glm::vec3(0.6, 0.6, 0.6), rodR*10, rodR*2);
	rod.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCylinder::M_PI / 2);
	rod.rotate(glm::vec3(0.0, 0.0, 1.0), BasicCylinder::M_PI / 2);

	CompositeGroup rods;
	// crate rods handles
	rod.translate(glm::vec3(lenght * 0.2, 0.0, -rodR * 2));
	rods.addObject(rod);
	rod.translate(glm::vec3(-lenght * 0.4, 0.0, 0.0));
	rods.addObject(rod);
	rod.translate(glm::vec3(lenght * 0.6, 0.0, rodR * 5));
	rods.addObject(rod);
	rod.translate(glm::vec3(-lenght * 0.8, 0.0, 0.0));
	rods.addObject(rod);

	this->addObject(rods);
}