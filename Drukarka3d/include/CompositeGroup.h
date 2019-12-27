#pragma once

#include "GraphicsObj.h"

class CompositeGroup : public GraphicsObj {
public:
	void addObject(GraphicsObj &model);
protected:
	void setModifiedVertInd();
};
