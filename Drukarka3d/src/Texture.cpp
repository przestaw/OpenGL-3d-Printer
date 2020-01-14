#include "Texture.h"

Texture::Texture() :id(0) {}

Texture::Texture(std::string path) : path(path) {
	loadTexture(path.c_str());
}

Texture::Texture(const Texture& other) : id(other.id), path(other.path) {}

GLuint Texture::getId() {
	return id;
}

void Texture::loadTexture(const char* fname) {
	int width, height;
	GLuint textureId;

	// Load tex
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception(fname);
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);
	//set Texture params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate tex
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// free and unbind
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set id
	this->id = textureId;
}