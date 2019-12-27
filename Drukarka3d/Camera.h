#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;


class Camera
{

public:

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   GLfloat yaw = YAW, GLfloat pitch = PITCH);

	// Returns view matrix for scene
	glm::mat4 getView();

	// Process events
	void handleKeyboard(Direction direction, GLfloat deltaTime);
	void handleMouseMovement(GLfloat xOffset, GLfloat yOffset);
	void handleMouseScroll(GLfloat yOffset);

	// Sets boundaries for camera meaning that camera will not leave a cuboid made out of two opposite vertices
	void setBoundries(glm::vec3 leftFrontBottom, glm::vec3 rightBackTop);
	void unsetBoundries();

	// Sets constrains for how far up can camera look
	void setPitchConstrains(GLfloat minPitch, GLfloat maxPitch);
	void unsetPitchConstraint();

	// Sets camera position in an instant
	void moveCamera(glm::vec3 position);

	GLfloat getZoom();

private:
	void updateVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	GLfloat yaw{ 0 };
	GLfloat pitch{ 0 };
	GLfloat movementSpeed{ 0 };
	GLfloat mouseSensitivity{ 0 };
	GLfloat zoom{ 0 };
	GLfloat minPitch;
	GLfloat maxPitch;
	bool pitchConstrainsSet{ false };

};

