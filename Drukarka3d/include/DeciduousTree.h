#pragma once

#include "ObjectGroup.h"

class DeciduousTree : public ObjectGroup {
public:
	DeciduousTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height, GLfloat radius, GLuint segments, Texture leavesTex = Texture(), Texture woodTex = Texture());
	virtual ~DeciduousTree() {}

};
