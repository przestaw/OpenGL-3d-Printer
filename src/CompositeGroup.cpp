#include "CompositeGroup.h"

void CompositeGroup::addObject(GraphicsObj& model) {
  unsigned firstNew = vertices.size();

  for (auto& it : model.vertices) {
    glm::vec4 vecPos = glm::vec4(it.Position, 1.0);

    vecPos = model.model * vecPos;

    this->vertices.push_back(
        Vertex(glm::vec3(vecPos), it.Color, it.TexCoords, it.Normal));
  }

  for (auto& it : model.indices) { this->indices.emplace_back(it + firstNew); }

  recalculateNormales();
  setModifiedVertInd();
}

void CompositeGroup::setModifiedVertInd() {
  vertices.shrink_to_fit();
  indices.shrink_to_fit();

  // Bind the Vertex Array Object first
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);

  // Color attribute
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, Color));

  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, TexCoords));
  glEnableVertexAttribArray(2);

  // Normal attribute
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, Normal));
  glEnableVertexAttribArray(3);

  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);

  // Unbind VAO
  glBindVertexArray(0);
}
