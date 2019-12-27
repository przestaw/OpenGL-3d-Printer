#pragma once

#include <memory>
#include <vector>
#include "AbstractObj.h"
#include "GraphicsObj.h"

class ObjectGroup : public AbstractObj {
public:
	ObjectGroup();
	virtual ~ObjectGroup() {}

	void addObject(std::unique_ptr<AbstractObj> &&model);

	void Draw(ShaderProgram shader);

protected:
	void Draw(ShaderProgram shader, const glm::mat4& parentMat) override;

	std::vector<std::unique_ptr<AbstractObj>> containedObjects;
private:

};