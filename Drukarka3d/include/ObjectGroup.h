#pragma once

#include <memory>
#include <vector>
#include "AbstractObj.h"
#include "GraphicsObj.h"

class ObjectGroup : public AbstractObj {
public:
	ObjectGroup();
	ObjectGroup(const ObjectGroup& other);
	virtual ~ObjectGroup() {}

	void copyObjects(const ObjectGroup& other);

	void addObject(std::unique_ptr<GraphicsObj> &&model);

	void addObject(const GraphicsObj &model);

	void Draw(ShaderProgram shader, const glm::mat4& parentMat = glm::mat4(1.0f)) override;

protected:

	std::vector<std::unique_ptr<GraphicsObj>> containedObjects;
};