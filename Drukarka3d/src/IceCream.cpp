#include "IceCream.h"
#include <BasicCone.h>
#include <BasicSphere.h>

IceCream::IceCream(GLfloat scale, glm::vec3 color) {
	// Make Demo wafer
	BasicCone cone = BasicCone(glm::vec3(0.0), scale * 0.7, 0, scale * 0.3);
	cone.setTexture(Texture("res/coneTex.png"), 1.0);

	// Make demo ice cream 
	BasicSphere sphere1 = BasicSphere(color, scale * 0.32, 24, 24);
	sphere1.translate(glm::vec3(.0f, 0.63 * scale, .0f));
	
	// Make demo cone
	this->addObject(cone);
	this->addObject(sphere1);

	this->translate(glm::vec3(0.0, scale * 0.3, 0.0));
}
