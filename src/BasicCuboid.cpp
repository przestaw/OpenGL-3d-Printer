#include "BasicCuboid.h"

BasicCuboid::BasicCuboid(glm::vec3 baseColor, GLfloat width, GLfloat height,
                         GLfloat lenght)
    : baseColor(baseColor), width(0.5f), height(height), lenght(lenght) {
  std::vector<std::pair<glm::vec3, glm::vec2>> verticesCoordinates = {
      {glm::vec3(-width / 2.0f, -height / 2.0f, lenght / 2.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(width / 2.0f, -height / 2.0f, lenght / 2.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(width / 2.0f, height / 2.0f, lenght / 2.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(-width / 2.0f, height / 2.0f, lenght / 2.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(-width / 2.0f, -height / 2.0f, -lenght / 2.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(width / 2.0f, -height / 2.0f, -lenght / 2.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(width / 2.0f, height / 2.0f, -lenght / 2.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(-width / 2.0f, height / 2.0f, -lenght / 2.0f),
       glm::vec2(0.0f, 1.0f)}};

  std::vector<Vertex> _vertices;
  for (unsigned int i = 0; i < verticesCoordinates.size(); ++i) {
    _vertices.push_back(Vertex(verticesCoordinates[i].first, baseColor,
                               verticesCoordinates[i].second, glm::vec3(0.0f)));
  }

  std::vector<GLuint> _indices = {// front
                                  2, 1, 0, 0, 3, 2,
                                  // right
                                  6, 5, 1, 1, 2, 6,
                                  // back
                                  5, 6, 7, 7, 4, 5,
                                  // left
                                  3, 0, 4, 4, 7, 3,
                                  // bottom
                                  1, 5, 4, 4, 0, 1,
                                  // top
                                  6, 2, 3, 3, 7, 6};

  /* Save calculated vertices and indices in the GraphicsObj fields, calculate
   * normales */
  setVertices(_vertices);
  setIndices(_indices);
  recalculateNormales();
}