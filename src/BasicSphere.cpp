#include "../include/BasicSphere.h"

const double BasicSphere::PI   = 3.14159265358979323846;
const double BasicSphere::C2PI = (PI * 2.);

BasicSphere::BasicSphere(glm::vec3 baseColor, GLfloat radius, GLuint nLatitudes,
                         GLuint nLongitudes)
    : baseColor(baseColor), radius(radius), nLatitudes(nLatitudes),
      nLongitudes(nLongitudes) {
  std::vector<Vertex> _vertices;

  /* Space between latitudes lines */
  GLfloat latitudeSpace = M_PI / nLatitudes;
  /* Space between longitude lines */
  GLfloat longitudeSpace = C2PI / nLongitudes;
  /* Number of vertices*/
  GLuint nVertices = (nLongitudes + 1) * (nLatitudes - 1) + 2;

  /*** Calculate vertices ***/

  // North pole
  _vertices.push_back(Vertex(glm::vec3(0.0f, radius, 0.0f), baseColor,
                             glm::vec2(0.5f, 1.0f), glm::vec3(0.0f)));

  // Body of the sphere
  for (unsigned int latitude = 1; latitude < nLatitudes; ++latitude) {
    for (unsigned int longitude = 0; longitude <= nLongitudes; ++longitude) {
      _vertices.push_back(Vertex(
          /* Coordinates */
          glm::vec3(radius * cos(longitude * longitudeSpace)
                        * sin(latitude * latitudeSpace),
                    radius * cos(latitude * latitudeSpace),
                    radius * sin(longitude * longitudeSpace)
                        * sin(latitude * latitudeSpace)),
          /* Color */
          baseColor,
          /* Texture */
          glm::vec2((GLfloat)longitude / nLongitudes,
                    1 - (GLfloat)latitude / nLatitudes),
          /* Normals */
          glm::vec3(0.0f)));
    }
  }

  // South pole
  _vertices.push_back(Vertex(glm::vec3(0.0f, -radius, 0.0f), baseColor,
                             glm::vec2(0.5f, 0.0f), glm::vec3(0.0f)));

  /**** Store indices ****/
  std::vector<GLuint> _indices;

  // North pole
  for (unsigned int i = 1; i <= nLongitudes; ++i) {
    _indices.push_back(0);
    _indices.push_back(i);
    _indices.push_back(i + 1);
  }
  // South pole
  int temp = nVertices - 1;
  for (int j = temp - 1; j > temp - nLongitudes - 1; j--) {
    _indices.push_back(temp);
    _indices.push_back(j);
    _indices.push_back(j - 1);
  }

  // Body of the sphere
  for (unsigned int i = 1; i < nLatitudes - 1; i++) {
    for (unsigned int j = 1; j <= nLongitudes; j++) {
      // First triangle of the quad
      _indices.push_back((i - 1) * nLongitudes + j);
      _indices.push_back(i * nLongitudes + j);
      _indices.push_back(i * nLongitudes + j + 1);
      // Second triangle of the quad
      _indices.push_back((i - 1) * nLongitudes + j);
      _indices.push_back(i * nLongitudes + j + 1);
      _indices.push_back((i - 1) * nLongitudes + j + 1);
    }
  }

  /* Save vertices and indices to the GraphicsObj fields, calculate normales */
  setVertices(_vertices);
  setIndices(_indices);
  recalculateNormales();
}