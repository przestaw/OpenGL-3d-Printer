#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>

class Texture {
public:
	Texture();
	Texture(std::string path);
	Texture(const Texture& other);

	GLuint getId();
private:
	GLuint id;
	std::string path;

	void loadTexture(const char* fname);
};