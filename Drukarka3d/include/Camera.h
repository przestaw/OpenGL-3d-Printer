#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Camera
{

public:
	// Default camera values
	static const GLfloat YAW;
	static const GLfloat PITCH;
	static const GLfloat SPEED;
	static const GLfloat SENSITIVITY;
	static const GLfloat ZOOM;
	static const GLfloat MIN_ZOOM;
	static const GLfloat MAX_ZOOM;

	enum Direction {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

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

	void checkBoundaries();

	GLfloat getZoom();
	glm::vec3 getPosition();

private:
	void updateVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::vec3 leftFrontBottomBoundary;
	glm::vec3 rightBackTopBoundary;
	bool boundariesSet{ false };
	GLfloat yaw{ 0 };
	GLfloat pitch{ 0 };
	GLfloat movementSpeed{ 0 };
	GLfloat mouseSensitivity{ 0 };
	GLfloat zoom{ 0 };
	GLfloat minPitch;
	GLfloat maxPitch;
	bool pitchConstrainsSet{ false };

};

