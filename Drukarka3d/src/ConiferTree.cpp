#include "ConiferTree.h"

#include "BasicCone.h"
#include <CompositeGroup.h>

ConiferTree::ConiferTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height, GLfloat radius, GLuint segments) {
	BasicCone woodCyl(wood, height, 0.00001 + radius * 0.15, 0.0);

	//woodCyl.translate(glm::vec3(0.0, -height * 0.4, 0.0));
	//woodCyl.setTexture(wood_tex, 0.8);

	this->addObject(woodCyl);

	GLfloat step =  2 * height / segments;

	CompositeGroup green;


	for (unsigned i = 0; i < segments; ++i) {
		BasicCone cone(leaves, step, 0.00001 + radius, radius * 0.2);
		radius = radius / 1.2;
		cone.translate(glm::vec3(0.0,  step * i, 0.0));
		//cone.setTexture(leaves_tex, 0.8);
		green.addObject(cone);
	}

	BasicCone cone(leaves, step, 0.00001 + radius, 0.0);
	radius = radius * 0.6;
	cone.translate(glm::vec3(0.0, step * segments, 0.0));
	//cone.setTexture(leaves_tex, 0.8);
	green.addObject(cone);

	this->addObject(green);
}
