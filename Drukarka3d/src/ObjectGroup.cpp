#include "..\include\ObjectGroup.h"

ObjectGroup::ObjectGroup() {
	this->model = glm::mat4(1.0f);
}

void ObjectGroup::addObject(std::shared_ptr<AbstractObj>&& model) {
	containedObjects.push_back(std::move(model));
}

void ObjectGroup::Draw(ShaderProgram shader, const glm::mat4& parentMat) {
	for (auto& it : containedObjects) {
		it->Draw(shader, parentMat * this->model);
	}
}
