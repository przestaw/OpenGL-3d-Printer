#include "..\include\Camera.h"

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
	if (boundariesSet) {
		checkBoundaries();
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

void Camera::setBoundries(glm::vec3 leftFrontBottom, glm::vec3 rightBackTop)
{
	if (leftFrontBottom.x > rightBackTop.x) {
		return;
	}
	if (leftFrontBottom.y > rightBackTop.y) {
		return;
	}
	if (leftFrontBottom.z > rightBackTop.z) {
		return;
	}

	this->leftFrontBottomBoundary = leftFrontBottom;
	this->rightBackTopBoundary = rightBackTop;
	boundariesSet = true;
}

void Camera::checkBoundaries()
{
	if (position.x > rightBackTopBoundary.x) {
		position.x = rightBackTopBoundary.x;
	}
	if (position.x < leftFrontBottomBoundary.x) {
		position.x = leftFrontBottomBoundary.x;
	}
	if (position.y > rightBackTopBoundary.y) {
		position.y = rightBackTopBoundary.y;
	}
	if (position.y < leftFrontBottomBoundary.y) {
		position.y = leftFrontBottomBoundary.y;
	}
	if (position.z > rightBackTopBoundary.z) {
		position.z = rightBackTopBoundary.z;
	}
	if (position.z < leftFrontBottomBoundary.z) {
		position.z = leftFrontBottomBoundary.z;
	}
}

void Camera::unsetBoundries()
{
	boundariesSet = false;
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
