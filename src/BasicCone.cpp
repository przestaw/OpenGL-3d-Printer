#include "../include/BasicCone.h"

const double BasicCone::PI   = 3.14159265358979323846;
const double BasicCone::C2PI = (BasicCone::PI * 2.);

BasicCone::BasicCone(glm::vec3 baseColor, GLfloat height, GLfloat bottomRadius,
                     GLfloat topRadius, unsigned nbSides)
    : height(height), bottomRadius(bottomRadius), topRadius(topRadius),
      nbSides(nbSides) {

  // Calculate Vertices and Triangles
  std::vector<std::pair<glm::vec3, glm::vec2>> v = vertices();
  std::vector<GLuint> t                          = triangles();
  std::vector<Vertex> vertices;

  // Assign base color to items
  for (unsigned i = 0; i < v.size(); i++) {
    vertices.push_back(
        Vertex(v[i].first, baseColor, v[i].second, glm::vec3(0.0f)));
  }

  // Set Vertices and Calc Normales
  setVertices(vertices);
  setIndices(t);
  recalculateNormales();
}

std::vector<std::pair<glm::vec3, glm::vec2>> BasicCone::vertices() {
  std::vector<std::pair<glm::vec3, glm::vec2>> vertices;
  unsigned vert = 0;

  // Bottom cap
  vertices.emplace_back(glm::vec3(0.0, -height / 2.0f, 0.0),
                        glm::vec2(0.5, 0.5));

  if (bottomRadius > 0) {
    for (vert = 0; vert < nbSides; vert++) {
      GLfloat part = (vert / (GLfloat)nbSides);
      GLfloat rad  = part * C2PI;

      part = (part > 0.5) ? 2 * (1.f - part) : 2 * part;

      vertices.emplace_back(glm::vec3(cos(rad) * bottomRadius, -height / 2.0f,
                                      sin(rad) * bottomRadius),
                            glm::vec2(0., part));
    }
  }

  // Top cap
  vertices.emplace_back(glm::vec3(0.0, height / 2.0f, 0.0),
                        glm::vec2(0.5, 0.5));
  if (topRadius > 0) {
    for (vert = 0; vert < nbSides; vert++) {
      GLfloat part = (vert / (GLfloat)nbSides);
      GLfloat rad  = part * C2PI;

      part = (part > 0.5) ? 2 * (1.f - part) : 2 * part;

      vertices.emplace_back(
          glm::vec3(cos(rad) * topRadius, height / 2.0f, sin(rad) * topRadius),
          glm::vec2(1., part));
    }
  }

  return vertices;
}

std::vector<GLuint> BasicCone::triangles() {
  std::vector<GLuint> triangles;

  // Bottom cap
  if (bottomRadius > 0) {
    for (unsigned i = 0; i < nbSides; i++) {
      triangles.push_back(0);
      triangles.push_back(((i + 1) % nbSides) + 1);
      triangles.push_back((i % nbSides) + 1);
    }
  }

  // Top cap
  if (topRadius > 0) {
    unsigned firstIdx = bottomRadius > 0 ? nbSides + 1 : 1;
    for (unsigned i = 0; i < nbSides; i++) {
      triangles.push_back(firstIdx);
      triangles.push_back((i % nbSides) + firstIdx + 1);
      triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
    }
  }

  // Sides
  if (topRadius > 0 && bottomRadius > 0) {
    for (unsigned i = 0; i < nbSides; i++) {
      std::vector<unsigned> tri =
          quadToTri((i % nbSides) + 1, ((i + 1) % nbSides) + 1,
                    ((i + 1) % nbSides) + 1 + nbSides + 1,
                    (i % nbSides) + 1 + nbSides + 1);
      triangles.insert(triangles.end(), tri.begin(), tri.end());
    }
  } else if (topRadius > 0) {
    unsigned firstIdx = 1;
    for (unsigned i = 0; i < nbSides; i++) {
      triangles.push_back(0);
      triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
      triangles.push_back((i % nbSides) + firstIdx + 1);
    }
  } else if (bottomRadius > 0) {
    unsigned firstIdx = 0;
    for (unsigned i = 0; i < nbSides; i++) {
      triangles.push_back((i % nbSides) + firstIdx + 1);
      triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
      triangles.push_back(nbSides + 1);
    }
  }

  return triangles;
}