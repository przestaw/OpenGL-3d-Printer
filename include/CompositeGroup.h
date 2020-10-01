#pragma once

#include "GraphicsObj.h"

class CompositeGroup : public GraphicsObj {
public:
  virtual ~CompositeGroup() {}

  void addObject(GraphicsObj &model);

protected:
  void setModifiedVertInd();
};
