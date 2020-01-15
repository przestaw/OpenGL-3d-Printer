#include "..\include\ObjectGroup.h"

ObjectGroup::ObjectGroup() {
	this->model = glm::mat4(1.0f);
}

ObjectGroup::ObjectGroup(const ObjectGroup& other) {
	copyObjects(other);
}

void ObjectGroup::copyObjects(const ObjectGroup& other) {
	for (auto& it : other.containedObjects) {
		auto temp = *it;
		temp.transform(other.model);
		this->addObject(temp);
	}
}

void ObjectGroup::addObject(std::unique_ptr<GraphicsObj>&& model) {
	containedObjects.push_back(std::move(model));
}

void ObjectGroup::addObject(const GraphicsObj &model){
	this->addObject(std::make_unique<GraphicsObj>(model));
}


void ObjectGroup::Draw(ShaderProgram shader, const glm::mat4& parentMat) {
	for (auto& it : containedObjects) {
		it->Draw(shader, (parentMat * this->model));
	}
}
