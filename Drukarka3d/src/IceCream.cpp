#include "IceCream.h"
#include <BasicCone.h>
#include <BasicSphere.h>

IceCream::IceCream(GLfloat scale, glm::vec3 color) {
	// Make Demo wafer
	BasicCone cone = BasicCone(glm::vec3(0.0), scale * 0.7, 0, scale * 0.3);
	Material wafer(0.01, Texture("res/coneTex.png"), 1.0, Texture("res/black.jpg"), 1.0);
	cone.setMaterial(wafer);

	// Make demo ice cream 
	BasicSphere sphere1 = BasicSphere(color, scale * 0.38, 24, 24);
	Material shine(186);
	sphere1.translate(glm::vec3(.0f, 0.6 * scale, .0f));
	sphere1.setMaterial(shine);
	// Make demo cone
	this->addObject(cone);
	this->addObject(sphere1);

	this->translate(glm::vec3(0.0, scale * 0.3, 0.0));
}
