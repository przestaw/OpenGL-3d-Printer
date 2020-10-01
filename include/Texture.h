#pragma once
#include <SOIL.h>
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <string>

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