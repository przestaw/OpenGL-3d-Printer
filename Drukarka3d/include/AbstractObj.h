#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <glew.h>

#include "shprogram.h"

class AbstractObj {
protected:
	glm::mat4 model;

public:
	AbstractObj() {}
	virtual ~AbstractObj() {}

	virtual void Draw(ShaderProgram shader) = 0;

	void translate(const glm::vec3& v) {
		model = glm::translate(model, v);
	}

	void rotate(const glm::vec3& axis, float angle) {
		model = glm::rotate(model, angle, axis);
	}

	void scale(const glm::vec3& scale) {
		model = glm::scale(model, scale);
	}

	void transform(const glm::mat4& transformation)
	{
		model = transformation * model;
	}
	
};

