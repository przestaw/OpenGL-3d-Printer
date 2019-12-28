#include "BasicCuboid.h"

BasicCuboid::BasicCuboid(glm::vec3 baseColor, GLfloat width, GLfloat height, GLfloat lenght)
	: baseColor(baseColor), width(0.5f), height(height), lenght(lenght)
{
	std::vector<glm::vec3> verticesCoordinates = {
		glm::vec3(-width / 2.0f, -height / 2.0f, -lenght / 2.0f),
		glm::vec3(width / 2.0f, -height  / 2.0f, -lenght / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f, -lenght / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f, -lenght / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f, lenght / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f, lenght / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f, lenght / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f, lenght / 2.0f),
	};

	std::vector<Vertex> _vertices;
	for (unsigned int i = 0; i < verticesCoordinates.size(); ++i)
	{
		_vertices.push_back(Vertex(verticesCoordinates[i], baseColor, glm::vec2(0.0f), glm::vec3(0.0f)));
	}

	std::vector<GLuint> _indices = {
		// back
		0, 1, 2,
		3, 1, 2,
		// front
		4, 5, 6,
		7, 5, 6,
		// left
		0, 4, 2,
		6, 4, 2,
		// right
		1, 5, 3,
		7, 5, 3,
		// bottom
		0, 1, 4,
		5, 1, 4,
		// top
		2, 3, 6,
		7, 3, 6
	};

	/* Save calculated vertices and indices in the GraphicsObj fields, calculate normales */
	setVertices(_vertices);
	setIndices(_indices);
	recalculateNormales();
}