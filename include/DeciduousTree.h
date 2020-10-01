#pragma once

#include "Material.h"
#include "ObjectGroup.h"

class DeciduousTree : public ObjectGroup {
public:
  DeciduousTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height,
                GLfloat radius, GLuint segments,
                Material leavesTex = Material(12),
                Material woodTex   = Material(12));
  virtual ~DeciduousTree() {}
};
