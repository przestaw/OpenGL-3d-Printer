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

	// crate table handlers
	CompositeGroup handles;

	BasicCuboid high(glm::vec3(0.6, 0.6, 0.6), rodR * 5, rodR * 4, rodR * 3);
	BasicCuboid low(glm::vec3(0.6, 0.6, 0.6), rodR * 5, rodR * 9, rodR * 3);

	high.translate(glm::vec3(0.0, rodR * 5, lenght * 0.2));
	low.translate(glm::vec3(0.0, rodR *2, lenght * 0.4));

	handles.addObject(high);
	handles.addObject(low);

	high.translate(glm::vec3(0.0, 0.0, - lenght * 0.4));
	low.translate(glm::vec3(0.0, 0.0, - lenght * 0.8));

	handles.addObject(high);
	handles.addObject(low);

	Material shine(186);
	handles.setMaterial(shine);
	rods.setMaterial(shine);

	// add 2 pairs
	handles.translate(glm::vec3(lenght * 0.1, 0.0, 0.0));
	rods.translate(glm::vec3(lenght * 0.1, 0.0, 0.0));
	this->addObject(handles);
	this->addObject(rods);

	handles.translate(glm::vec3(-lenght * 0.2, 0.0, 0.0));
	rods.translate(glm::vec3(-lenght * 0.2, 0.0, 0.0));
	this->addObject(handles);
	this->addObject(rods);

	BasicCuboid table(glm::vec3(0.8, 0.1, 0.1), lenght*0.85, 2*rodR, lenght * 0.85);

	table.translate(glm::vec3(0.0, 7 * rodR, 0.0));
	table.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCone::M_PI);
	Material grill(64, Texture("res/coneTex.png"), 0.5, Texture("res/coneTex.png"), 0.2);
	
	table.setMaterial(grill);

	this->addObject(table);
}