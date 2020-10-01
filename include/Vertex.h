#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
  Vertex(glm::vec3 Position, glm::vec3 Color, glm::vec2 TexCoords,
         glm::vec3 Normal)
      : Position(Position), Color(Color), TexCoords(TexCoords), Normal(Normal) {
  }

  // self descriptive
  glm::vec3 Position;
  glm::vec3 Color;
  glm::vec2 TexCoords;
  glm::vec3 Normal;
};
