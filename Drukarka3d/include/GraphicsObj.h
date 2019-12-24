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
	// Triangles and Indices, vector allows for easy modification
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	// Texture ??

	GraphicsObj();

	void setVertices(std::vector<Vertex> v);

	void setIndices(std::vector<unsigned int> i);

	void recalculateNormales();
private:
	// Vertex Buffer Object 
	GLuint VBO, 
	//and Element Buffer Object
			   EBO;
};