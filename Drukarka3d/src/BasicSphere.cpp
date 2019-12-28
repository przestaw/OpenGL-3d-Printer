#include "../include/BasicSphere.h"

BasicSphere::BasicSphere(glm::vec3 baseColor, GLfloat radius, GLuint nLatitudes, GLuint nLongitudes)
	: baseColor(baseColor), radius(radius), nLatitudes(nLatitudes), nLongitudes(nLongitudes)
{
	std::vector<glm::vec3> verticesCoordinates;
	std::vector<glm::vec3> normals;

	/* Space between latitudes lines */
	GLfloat latitudeSpace = PI_F / nLatitudes;
	/* Space between longitude lines */
	GLfloat longitudeSpace = 2 * PI_F / nLongitudes;
	/* Number of vertices*/
	GLuint nVertices = (nLongitudes + 1) * (nLatitudes - 1) + 2;

	/*** Calculate vertices ***/

	// North pole
	verticesCoordinates.push_back(glm::vec3(0.0f, radius, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	// Body of the sphere
	for (unsigned int longitude = 0; longitude <= nLongitudes; ++longitude)
	{
		for (unsigned int latitude = 1; latitude < nLatitudes; ++latitude)
		{
			verticesCoordinates.push_back(
				glm::vec3(
					radius * cos(longitude * longitudeSpace) * sin(latitude * latitudeSpace),
					radius * cos(latitude * latitudeSpace),
					radius * sin(longitude * longitudeSpace) * sin(latitude * latitudeSpace)
				)
			);
			normals.push_back(
				glm::vec3(
					sin(latitudeSpace * latitude) * cos(longitudeSpace * longitude),
					cos(latitudeSpace * latitude),
					sin(latitudeSpace * latitude) * sin(longitudeSpace * longitude)
				)
			);
		}
	}

	// South pole
	verticesCoordinates.push_back(glm::vec3(0.0f, -radius, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	// Create vertices
	std::vector<Vertex> _vertices;
	for (unsigned int i = 0; i < nVertices; ++i)
	{
		_vertices.push_back(Vertex(verticesCoordinates[i], baseColor, glm::vec2(0.0f), normals[i]));
	}
	
	/**** Store indices ****/
	std::vector<GLuint> _indices;

	// North pole
	for (unsigned int i = 1; i <= nLongitudes; ++i)
	{
		_indices.push_back(0);
		_indices.push_back(i);
		_indices.push_back(i + 1);
	}
	// South pole
	int temp = nVertices - 1;
	for (int j = temp - 1; j > temp - nLongitudes - 1; j--) 
	{
		_indices.push_back(temp);
		_indices.push_back(j);
		_indices.push_back(j - 1);
	}

	// Body of the sphere
	for (unsigned int i = 1; i < nLatitudes - 1; i++)
	{
		for (unsigned int j = 1; j <= nLongitudes; j++)
		{
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