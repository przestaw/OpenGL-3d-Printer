#pragma once

#include "ObjectGroup.h"

class DeciduousTree : public ObjectGroup {
	DeciduousTree(glm::vec3 leaves, Texture leaves_tex, glm::vec3 wood, Texture wood_tex, GLfloat height, GLfloat radius, GLuint segments);
	virtual ~DeciduousTree() {}

};
