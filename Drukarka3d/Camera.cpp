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

void Camera::handleMouseMovement(GLfloat xOffset, GLfloat yOffset)
{
	xOffset = xOffset * mouseSensitivity;
	yOffset = yOffset * mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitchConstrainsSet) {
		if (pitch > maxPitch) {
			pitch = maxPitch;
		}
		if (pitch < minPitch) {
			pitch = minPitch;
		}
	}

	updateVectors();
}

void Camera::handleMouseScroll(GLfloat yOffset)
{
	zoom -= yOffset;

	if (zoom > MAX_ZOOM) {
		zoom = MAX_ZOOM;
	}
	if (zoom < MIN_ZOOM) {
		zoom = MIN_ZOOM;
	}
}

void Camera::setPitchConstrains(GLfloat minPitch, GLfloat maxPitch)
{
	if (minPitch > maxPitch) {
		pitchConstrainsSet = false;
		return;
	}

	this->minPitch = minPitch;
	this->maxPitch = maxPitch;
	pitchConstrainsSet = true;
}

void Camera::unsetPitchConstraint()
{
	pitchConstrainsSet = false;
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
