#include "AbstractObj.h"

void AbstractObj::translate(const glm::vec3& v) {
	model = glm::translate(model, v);
}

void AbstractObj::rotate(const glm::vec3& axis, float angle) {
	model = glm::rotate(model, angle, axis);
}

void AbstractObj::scale(const glm::vec3& scale) {
	model = glm::scale(model, scale);
}

void AbstractObj::transform(const glm::mat4& transformation) {
	model = transformation * model;
}