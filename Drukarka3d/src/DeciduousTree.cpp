#include "DeciduousTree.h"
#include <random>
#include <BasicCone.h>
#include <CompositeGroup.h>
#include <BasicSphere.h>


DeciduousTree::DeciduousTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height, GLfloat radius, GLuint segments, Texture leavesTex, Texture woodTex) {
	std::mt19937_64 myRand(std::random_device{}());
	std::normal_distribution<GLfloat> myRandFloat(0.0, 0.8 * radius);
	BasicCone woodCyl(wood, height, radius * 0.35, radius * 0.2);

	woodCyl.translate(glm::vec3(0.0, -height * 0.6, 0.0));
	if (woodTex.getId() != 0)
		woodCyl.setTexture(woodTex, 0.6);

	this->addObject(woodCyl);

	GLfloat step = height / segments;
	radius = radius / 2.0;
	CompositeGroup green;
	BasicSphere bot(leaves, radius);
	green.addObject(bot);

	for (unsigned i = 0; i < segments; ++i) {
		unsigned j = i <= (segments / 2) ? i : ((segments - i) / 2);
		++j;
		for (; j > 0; --j) {
			GLfloat move = (i - segments / 2.0) * radius / segments;
			BasicSphere sphere(leaves, radius * (1.0 + (segments - i)*0.1), 24, 24);

			GLfloat moveX = myRandFloat(myRand) * move;
			GLfloat moveY = myRandFloat(myRand) * move;
			moveX = myRand() % 2 == 1 ? moveX : -moveX;
			moveY = myRand() % 2 == 1 ? moveY : -moveY;
			sphere.translate(glm::vec3(moveX, step * i, moveY));
			green.addObject(sphere);
		}
	}

	BasicSphere top(leaves, radius, 24, 24);
	top.translate(glm::vec3(0.0, step * segments, 0.0));
	if (leavesTex.getId() != 0)
		green.setTexture(leavesTex, 0.6);
	green.addObject(top);

	this->addObject(green);
	this->translate(glm::vec3(0.0, height * 0.75, 0.0));
}
