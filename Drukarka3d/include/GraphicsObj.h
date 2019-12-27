#pragma once

#include "AbstractObj.h"
#include "Vertex.h"

#include <vector>

class GraphicsObj : public AbstractObj {
public:

	~GraphicsObj();

	void Draw(ShaderProgram shader);
protected:
	// Vertex Array Object
	GLuint VAO;
	// Vertex Buffer Object 
	GLuint VBO;
	// Element Buffer Object
	GLuint EBO;
	// Texture ??

	// Triangles and Indices, vector allows for easy modification
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	
	GraphicsObj();

	void setVertices(std::vector<Vertex> vertices);

	void setIndices(std::vector<unsigned int> indices);

	void recalculateNormales();

	friend class CompositeGroup;
};