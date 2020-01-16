#pragma once

#include "AbstractObj.h"
#include "Vertex.h"
#include "Texture.h"
#include <vector>

class GraphicsObj : public AbstractObj {
public:
	virtual ~GraphicsObj();

	void Draw(ShaderProgram shader, const glm::mat4& parentMat = glm::mat4(1.0f));

	void setTexture(const Texture &texture, const GLfloat texImpact);

	void setDiffuseMap(const Texture& map, const GLfloat mapImpact);

	void setSpecularMap(const Texture& map, const GLfloat mapImpact);

	// Preferably a power of two
	void setShininess(const GLfloat shininess);


	GraphicsObj(const GraphicsObj& other);
protected:
	// Vertex Array Object
	GLuint VAO;
	// Vertex Buffer Object 
	GLuint VBO;
	// Element Buffer Object
	GLuint EBO;
	// Light maps
	Texture diffuseTex;
	Texture specularTex;
	// Impact of light maps
	GLfloat diffuseImpact;
	GLfloat specularImpact;
	// Shininess
	GLfloat shininess;

	// Triangles and Indices, vector allows for easy modification
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	
	GraphicsObj();

	void setVertices(std::vector<Vertex> vertices);

	void setIndices(std::vector<unsigned int> indices);

	void recalculateNormales();

	friend class CompositeGroup;
};