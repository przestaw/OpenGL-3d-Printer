#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) 
	:	front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movementSpeed(SPEED),
		mouseSensitivity(SENSITIVITY),
		zoom(ZOOM),
		position(position),
		worldUp(up),
		yaw(yaw),
		pitch(pitch)
{
	updateVectors();
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::handleKeyboard(Direction direction, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;

	if (direction == Direction::FORWARD) {
		position += front * velocity;
	}
	if (direction == Direction::BACKWARD) {
		position -= front * velocity;
	}
	if (direction == Direction::RIGHT) {
		position += right * velocity;
	}
	if (direction == Direction::LEFT) {
		position -= right * velocity;
	}
}

GLfloat Camera::getZoom()
{
	return zoom;
}

void Camera::updateVectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
