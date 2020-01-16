#pragma once

#include "ConiferTree.h"
#include "DeciduousTree.h"
#include "IceCream.h"

class Forrest : public ObjectGroup {
public:
	Forrest(GLfloat centerR, GLfloat outerR, GLfloat heightUnit, unsigned coniferCount, unsigned deciduousCount, Texture woodTex, Texture deciduousGreen, Texture coniferGreen, unsigned iceCreamCount = 8);
	virtual ~Forrest() {}
};
