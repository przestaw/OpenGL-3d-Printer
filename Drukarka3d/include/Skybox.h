#pragma once

#include <vector>
#include <string>
#include <SOIL.h>
#include "AbstractObj.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void Draw();

	/* Provide vector of 6 textures (filepaths) for each face of the skybox cubemap */
	void setCubemapFaces(const std::vector<std::string> faces);

private:
	GLuint cubemapTexture;		// ID of the texture.
	GLuint VBO;
	GLuint VAO;
};