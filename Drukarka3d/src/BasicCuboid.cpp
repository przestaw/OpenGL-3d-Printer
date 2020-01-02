#include "BasicCuboid.h"

BasicCuboid::BasicCuboid(glm::vec3 baseColor, GLfloat width, GLfloat height, GLfloat lenght)
	: baseColor(baseColor), width(0.5f), height(height), lenght(lenght)
{
	std::vector<std::pair<glm::vec3, glm::vec2>> verticesCoordinates =
	{
		{glm::vec3(-width / 2.0f, -height / 2.0f, -lenght / 2.0f), glm::vec2(0.33f, 0.5f)},
		{glm::vec3(width / 2.0f, -height / 2.0f, -lenght / 2.0f), glm::vec2(0.66f, 0.5f)},
		{glm::vec3(-width / 2.0f, height / 2.0f, -lenght / 2.0f), glm::vec2(0.33f, 0.0f)},
		{glm::vec3(width / 2.0f, height / 2.0f, -lenght / 2.0f), glm::vec2(0.66f, 0.0f)},
		{glm::vec3(-width / 2.0f, -height / 2.0f, lenght / 2.0f), glm::vec2(0.0f, 0.5f)},
		{glm::vec3(width / 2.0f, -height / 2.0f, lenght / 2.0f), glm::vec2(0.33f, 0.5f)},
		{glm::vec3(-width / 2.0f, height / 2.0f, lenght / 2.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(width / 2.0f, height / 2.0f, lenght / 2.0f), glm::vec2(0.33f, 0.0f)}
	};

	std::vector<Vertex> _vertices;
	for (unsigned int i = 0; i < verticesCoordinates.size(); ++i)
	{
		_vertices.push_back(Vertex(verticesCoordinates[i].first, baseColor, verticesCoordinates[i].second, glm::vec3(0.0f)));
	}

	std::vector<GLuint> _indices = {
		// back
		0, 1, 2,
		3, 2, 1,
		// front
		4, 5, 6,
		7, 6, 5,
		// left
		0, 4, 2,
		6, 2, 4,
		// right
		1, 5, 3,
		7, 3, 5,
		// bottom
		4, 5, 0,
		1, 0, 5,
		// top
		6, 7, 2,
		3, 7, 6
	};

	/* Save calculated vertices and indices in the GraphicsObj fields, calculate normales */
	setVertices(_vertices);
	setIndices(_indices);
	recalculateNormales();
}