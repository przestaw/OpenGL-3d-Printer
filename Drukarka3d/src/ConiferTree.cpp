#include "ConiferTree.h"

#include "BasicCone.h"
#include <CompositeGroup.h>

ConiferTree::ConiferTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height, GLfloat radius, GLuint segments, Texture leavesTex, Texture woodTex) {
	BasicCone woodCyl(wood, height, radius * 0.2, radius * 0.15);

	woodCyl.translate(glm::vec3(0.0, -height * 0.45, 0.0));
	if (woodTex.getId() != 0)
		woodCyl.setTexture(woodTex, 0.6);
	
	this->addObject(woodCyl);

	GLfloat step =  1.2 * height / segments;

	CompositeGroup green;

	for (unsigned i = 0; i <= segments; ++i) {
		BasicCone cone(leaves, step, radius, radius * 0.45);
		radius = radius / 1.2;
		cone.translate(glm::vec3(0.0, step * i, 0.0));
		green.addObject(cone);
	}

	BasicCone top(leaves, step, radius, 0.0);
	radius = radius * 0.6;
	top.translate(glm::vec3(0.0, step * ++segments, 0.0));
	green.addObject(top);

	if (leavesTex.getId() != 0)
		green.setTexture(leavesTex, 0.6);

	green.translate(glm::vec3(0.0, -(height - step*segments/2.2), 0.0));

	this->addObject(green);
	this->translate(glm::vec3(0.0, height * 0.75, 0.0));
}
