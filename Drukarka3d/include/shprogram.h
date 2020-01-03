#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glew.h>

class ShaderProgram {
	GLuint program_id; 	// The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Use the program
	void Use() const {
		glUseProgram(get_programID());
	}

	// returns program ID
	GLuint get_programID() const {
		return program_id;
	}

	// used to set for example model matrix [from AbstractObj]
	inline void setMat4Uniform(const std::string& name, const glm::mat4& mat) const {
		glUniformMatrix4fv(glGetUniformLocation(get_programID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	// used to set any Vec4 parameter for shader
	inline void setVec4Uniform(const std::string& name, const glm::vec4& vec) const {
		glUniform4fv(glGetUniformLocation(get_programID(), name.c_str()), 1, &vec[0]);
	}

	// used to set any Vec3 parameter for shader
	inline void setVec3Uniform(const std::string& name, const glm::vec3& vec) const {
		glUniform3fv(glGetUniformLocation(get_programID(), name.c_str()), 1, &vec[0]);
	}

	// used to set any Vec2 parameter for shader
	inline void setVec2Uniform(const std::string& name, const glm::vec2& vec) const {
		glUniform2fv(glGetUniformLocation(get_programID(), name.c_str()), 1, &vec[0]);
	}

	// used to set any float parameter for shader
	inline void setFloatUniform(const std::string& name, const GLfloat value) const {
		glUniform1f(glGetUniformLocation(get_programID(), name.c_str()), value);
	}

	// used to set any unsigned int parameter for shader
	inline void setUnsignedIntUniform(const std::string& name, const GLuint value) const {
		glUniform1ui(glGetUniformLocation(get_programID(), name.c_str()), value);
	}

	// used to set any unsigned int parameter for shader
	inline void setIntUniform(const std::string& name, const GLint value) const {
		glUniform1i(glGetUniformLocation(get_programID(), name.c_str()), value);
	}
};