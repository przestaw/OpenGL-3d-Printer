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
	//Matrix of transformation for the object
	glm::mat4 model;
public:
	AbstractObj() {}
	virtual ~AbstractObj() {}

	virtual void Draw(ShaderProgram shader) = 0;

	void translate(const glm::vec3& v); 

	void rotate(const glm::vec3& axis, float angle);

	void scale(const glm::vec3& scale);

	void transform(const glm::mat4& transformation);
};

