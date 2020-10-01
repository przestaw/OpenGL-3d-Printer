#include "Digit.h"
#include "BasicCuboid.h"
#include "BasicCylinder.h"

Digit::Digit(GLfloat scale) {
  this->scale     = scale;
  glm::vec3 color = glm::vec3(0.85f, 0.15f, 0.0f);
  GLfloat width   = scale / 100;
  GLfloat height  = scale / 50;
  GLfloat lenght  = scale / 200;

  for (auto i = 0; i < 7; ++i)
    segments.push_back(BasicCuboid(color, width, height, lenght));

  // Left bottom
  segments[0].translate(glm::vec3(-height * 0.7, -height * 0.7, lenght));
  // Left top
  segments[1].translate(glm::vec3(-height * 0.7, height * 0.7, lenght));
  // Top
  segments[2].translate(glm::vec3(0.0f, height * 1.2, lenght));
  segments[2].rotate(glm::vec3(0.0f, 0.0f, 1.0f), BasicCylinder::PI / 2);
  // Right top
  segments[3].translate(glm::vec3(height * 0.7, height * 0.7, lenght));
  // Right bottom
  segments[4].translate(glm::vec3(height * 0.7, -height * 0.7, lenght));
  // Bottom
  segments[5].translate(glm::vec3(0.0f, -height * 1.2, lenght));
  segments[5].rotate(glm::vec3(0.0f, 0.0f, 1.0f), BasicCylinder::PI / 2);
  // Middle
  segments[6].translate(glm::vec3(0.0f, 0.0f, lenght));
  segments[6].rotate(glm::vec3(0.0f, 0.0f, 1.0f), BasicCylinder::PI / 2);
}

Digit::~Digit() {}

void Digit::Draw(ShaderProgram shader, const glm::mat4& parentMat) {
  this->Draw(shader, parentMat, 0);
}
void Digit::Draw(ShaderProgram shader, const glm::mat4& parentMat,
                 GLshort digit) {
  switch (digit) {
  case 0:
    for (GLuint i = 0; i < 6; ++i) {
      segments[i].Draw(shader, parentMat * this->model);
    }
    break;
  case 1:
    segments[3].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    break;
  case 2:
    segments[0].Draw(shader, parentMat * this->model);
    segments[2].Draw(shader, parentMat * this->model);
    segments[3].Draw(shader, parentMat * this->model);
    segments[5].Draw(shader, parentMat * this->model);
    segments[6].Draw(shader, parentMat * this->model);
    break;
  case 3:
    segments[2].Draw(shader, parentMat * this->model);
    segments[3].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    segments[5].Draw(shader, parentMat * this->model);
    segments[6].Draw(shader, parentMat * this->model);
    break;
  case 4:
    segments[1].Draw(shader, parentMat * this->model);
    segments[3].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    segments[6].Draw(shader, parentMat * this->model);
    break;
  case 5:
    segments[1].Draw(shader, parentMat * this->model);
    segments[2].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    segments[5].Draw(shader, parentMat * this->model);
    segments[6].Draw(shader, parentMat * this->model);
    break;
  case 6:
    segments[0].Draw(shader, parentMat * this->model);
    segments[1].Draw(shader, parentMat * this->model);
    segments[2].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    segments[5].Draw(shader, parentMat * this->model);
    segments[6].Draw(shader, parentMat * this->model);
    break;
  case 7:
    segments[2].Draw(shader, parentMat * this->model);
    segments[3].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    break;
  case 8:
    for (auto& it : segments) { it.Draw(shader, (parentMat * this->model)); }
    break;
  case 9:
    segments[1].Draw(shader, parentMat * this->model);
    segments[2].Draw(shader, parentMat * this->model);
    segments[3].Draw(shader, parentMat * this->model);
    segments[4].Draw(shader, parentMat * this->model);
    segments[5].Draw(shader, parentMat * this->model);
    segments[6].Draw(shader, parentMat * this->model);
    break;
  default:
    for (auto& it : segments) { it.Draw(shader, (parentMat * this->model)); }
    break;
  }
}