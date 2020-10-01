#pragma once

#include "ObjectGroup.h"

class IceCream : public ObjectGroup {
public:
  IceCream(GLfloat scale, glm::vec3 color = glm::vec3(0.9f, 0.5f, 0.6f));
  virtual ~IceCream() {}
};