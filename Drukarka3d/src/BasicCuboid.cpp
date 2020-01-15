#include "BasicCuboid.h"

BasicCuboid::BasicCuboid(glm::vec3 baseColor, GLfloat width, GLfloat height, GLfloat lenght)
	: baseColor(baseColor), width(0.5f), height(height), lenght(lenght)
{
	std::vector<std::pair<glm::vec3, glm::vec2>> verticesCoordinates =
	{
		{glm::vec3(-width / 2.0f, -height / 2.0f, lenght / 2.0f), glm::vec2(0.33f, 0.5f)},
		{glm::vec3(width / 2.0f, -height / 2.0f, lenght / 2.0f), glm::vec2(0.66f, 0.5f)},
		{glm::vec3(width / 2.0f, height / 2.0f, lenght / 2.0f), glm::vec2(0.33f, 0.0f)},
		{glm::vec3(-width / 2.0f, height / 2.0f, lenght / 2.0f), glm::vec2(0.66f, 0.0f)},
		{glm::vec3(-width / 2.0f, -height / 2.0f, -lenght / 2.0f), glm::vec2(0.0f, 0.5f)},
		{glm::vec3(width / 2.0f, -height / 2.0f, -lenght / 2.0f), glm::vec2(0.33f, 0.5f)},
		{glm::vec3(width / 2.0f, height / 2.0f, -lenght / 2.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-width / 2.0f, height / 2.0f, -lenght / 2.0f), glm::vec2(0.33f, 0.0f)}
	};

	std::vector<Vertex> _vertices;
	for (unsigned int i = 0; i < verticesCoordinates.size(); ++i)
	{
		_vertices.push_back(Vertex(verticesCoordinates[i].first, baseColor, verticesCoordinates[i].second, glm::vec3(0.0f)));
	}

	std::vector<GLuint> _indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	/* Save calculated vertices and indices in the GraphicsObj fields, calculate normales */
	setVertices(_vertices);
	setIndices(_indices);
	recalculateNormales();
}