#pragma once

#include "AbstractObj.h"
#include <SOIL.h>
#include <string>
#include <vector>

class Skybox {
public:
  Skybox(const std::vector<std::string>& faces);
  ~Skybox();

  void Draw(ShaderProgram shader, glm::mat3 cameraView, glm::mat4 projection);

private:
  /* Provide vector of 6 textures (filepaths) for each face of the skybox
   * cubemap */
  void setCubemapFaces(const std::vector<std::string>& faces);

  GLuint cubemapTexture; // ID of the texture.
  GLuint VBO;
  GLuint VAO;
};