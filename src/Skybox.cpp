#include "../include/Skybox.h"
#include <stdexcept>

Skybox::Skybox(const std::vector<std::string> &faces) {
  /* For skybox drawing we will use a cube of 36 vertices (and use
   * glDrawArrays()) */
  GLfloat vertices[] = {
      -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f,
      -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,

      1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,

      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,

      -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
  };

  // Generate buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Buffer the vertices data
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
  // Tell openGL how to interpret the data (3 contiguous values per vertex)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // Unbind VAO - just in case.
  glBindVertexArray(0);

  setCubemapFaces(faces);
}

Skybox::~Skybox() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Skybox::Draw(ShaderProgram shader, glm::mat3 cameraView,
                  glm::mat4 projection) {
  shader.Use();

  // We want to remove translation from the view matrix so that camera movement
  // doesn't affect the skybox's position vectors.
  shader.setMat4Uniform("view", glm::mat4(cameraView));
  shader.setMat4Uniform("projection", projection);

  // Change depth function so depth test passes when values are equal to depth
  // buffer's content.
  glDepthFunc(GL_LEQUAL);

  // Draw skybox
  glBindVertexArray(VAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Unbind VAO
  glBindVertexArray(0);
  // Change depth function back to default
  glDepthFunc(GL_LESS);
}

void Skybox::setCubemapFaces(const std::vector<std::string> &faces) {
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nChannels;
  for (GLuint i = 0; i < faces.size(); ++i) {
    unsigned char *image = SOIL_load_image(faces[i].c_str(), &width, &height,
                                           &nChannels, SOIL_LOAD_RGB);
    if (image == nullptr) {
      throw std::runtime_error("Failed to load cubemap texture file!");
    }
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  cubemapTexture = textureID;
}