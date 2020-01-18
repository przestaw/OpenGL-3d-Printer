#include "../include/Terrain.h"
#include <random>

Terrain::Terrain(GLfloat width, GLfloat lenght, GLuint subdivisions, GLfloat maxHeight, bool textureMappingByPrzemek)
{	
	/* Generate vertices */
	std::vector<Vertex> vertices_;

	std::mt19937_64 myRand(std::random_device{}());
	std::uniform_real_distribution<GLfloat> myRandFloat(-0.65, 0.65);

	// Generate first vertex, with completely random height from the range [0, maxHeight).
	// Height of every next vertex will depend on the height of the previous one.
	GLfloat height = (myRand() % static_cast<GLuint>(maxHeight * 100)) / 100.0f;
	glm::vec3 position = glm::vec3(-width / 2.0f, height, lenght / 2.0f);
	glm::vec3 color = glm::vec3(0.01f, 0.75f, 0.1f);
	glm::vec2 texCoord = glm::vec2(0.0f, 0.0f);
	vertices_.push_back(Vertex(position, color, texCoord, glm::vec3(0.0f)));

	GLfloat lastHeight = height;

	// Generate all vertices
	for (GLuint row = 0; row <= subdivisions; ++row)
	{
		for (GLuint col = 0; col <= subdivisions; ++col)
		{
			if (row == 0 && col == 0) continue;

			height = 0.5f * (lastHeight + myRandFloat(myRand) * maxHeight);
			if (height > maxHeight) height = maxHeight;
			else if (height < 0.0f) height = 0.0;
			lastHeight = height;

			position = glm::vec3(col * width / subdivisions - width / 2.0f, 
			                               height, 
				                           ((subdivisions - row) * lenght) / subdivisions - (lenght / 2.0f));
			texCoord = textureMappingByPrzemek ?
			            glm::vec2(static_cast<GLfloat>(col % 2), static_cast<GLfloat>(row % 2)) :
			            glm::vec2(0.05 * col, 0.05 *row);
			vertices_.push_back(Vertex(position, color, texCoord, glm::vec3(0.0f)));
		}
	}

	/* Generate indices */
	std::vector<GLuint> indices_;

	for (GLuint row = 0; row < subdivisions; row++) 
	{
		for (GLuint col = 0; col < subdivisions; col++) 
		{
			indices_.push_back(col + row * (subdivisions + 1));
			indices_.push_back(col + 1 + (row + 1) * (subdivisions + 1));
			indices_.push_back(col + 1 + row * (subdivisions + 1));

			indices_.push_back(col + row * (subdivisions + 1));
			indices_.push_back(col + (row + 1) * (subdivisions + 1));
			indices_.push_back(col + 1 + (row + 1) * (subdivisions + 1));
		}
	}

	/* Set GraphicsObj fields and calculate normals */
	setVertices(vertices_);
	setIndices(indices_);
	recalculateNormales();
}