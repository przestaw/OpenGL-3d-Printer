#pragma once

#include "ObjectGroup.h"

class ConiferTree : public ObjectGroup {
public:
	ConiferTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height, GLfloat radius, GLuint segments, Texture leavesTex = Texture(), Texture woodTex = Texture());
	virtual ~ConiferTree() {}
};
