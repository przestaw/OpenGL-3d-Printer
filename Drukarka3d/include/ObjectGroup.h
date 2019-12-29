#pragma once

#include <memory>
#include <vector>
#include "AbstractObj.h"
#include "GraphicsObj.h"

class ObjectGroup : public AbstractObj {
public:
	ObjectGroup();
	virtual ~ObjectGroup() {}

	void addObject(std::shared_ptr<AbstractObj> &&model);

	void Draw(ShaderProgram shader, const glm::mat4& parentMat = glm::mat4(1.0f)) override;

protected:

	std::vector<std::shared_ptr<AbstractObj>> containedObjects;
};