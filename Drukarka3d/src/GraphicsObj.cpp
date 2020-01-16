#include "../include/GraphicsObj.h"

GraphicsObj::GraphicsObj() : diffuseImpact(0.0f), specularImpact(0.0f), shininess(32.0f) {
	// Generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

GraphicsObj::~GraphicsObj() {
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void GraphicsObj::Draw(ShaderProgram shader, const glm::mat4& parentMat) {
	// Move object to desired place using AbstractObj model
	glm::mat4 finalModel = parentMat * model;
	shader.setMat4Uniform("model", finalModel);
	shader.setMat4Uniform("normalTrans", glm::transpose(glm::inverse(finalModel)));
	shader.setFloatUniform("material.diffuseImpact", diffuseImpact);
	shader.setFloatUniform("material.specularImpact", specularImpact);
	shader.setFloatUniform("material.shininess", shininess);

	// Choose light maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex.getId()); 

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTex.getId());

	// Bind the Vertex Array Object
	glBindVertexArray(VAO);
	// Draw Object
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// Unbind VAO
	glBindVertexArray(0);
}

// DEPRECATED please use setDiffuseMap and setSpecularMap
void GraphicsObj::setTexture(const Texture& texture, const GLfloat texIm) {
	setDiffuseMap(texture, texIm);
	setSpecularMap(texture, texIm);
}

void GraphicsObj::setDiffuseMap(const Texture& map, const GLfloat mapImpact)
{
	diffuseTex = map;

	diffuseImpact = ((mapImpact > 0.0f) ? ((mapImpact <= 1.0) ? mapImpact : 1.0) : 0.0);
}

void GraphicsObj::setSpecularMap(const Texture& map, const GLfloat mapImpact)
{
	specularTex = map;

	specularImpact = ((mapImpact > 0.0f) ? ((mapImpact <= 1.0) ? mapImpact : 1.0) : 0.0);
}

void GraphicsObj::setShininess(const GLfloat shininess)
{
	this->shininess = shininess;
}

GraphicsObj::GraphicsObj(const GraphicsObj& other) : GraphicsObj() {
	this->model = other.model;
	this->setVertices(std::vector<Vertex>(other.vertices));
	this->setIndices(std::vector<unsigned int>(other.indices));

	// Copy material
	this->diffuseTex = other.diffuseTex;
	this->diffuseImpact = other.diffuseImpact;
	this->specularTex = other.specularTex;
	this->specularImpact = other.specularImpact;
	this->shininess = other.shininess;
}

void GraphicsObj::setVertices(std::vector<Vertex> vertices_a) {
	// Assign Vertices
	vertices = vertices_a; //copy to object field
	vertices.shrink_to_fit();

	// Bind the Vertex Array Object first
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	glEnableVertexAttribArray(1);

	// Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	// Normal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(3);

	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);
}

void GraphicsObj::setIndices(std::vector<unsigned int> indices_a) {
	// Assign indices
	indices = indices_a; //copy to object field
	indices.shrink_to_fit();

	// Bind the Vertex Array Object 
	glBindVertexArray(VAO);

	// Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);
}

void GraphicsObj::recalculateNormales() {
	// Zero all normales
	for (unsigned i = 0; i < vertices.size(); i++) {
		vertices[i].Normal = glm::vec3(0.0f);
	}

	// Calc normales for faces and add to vertices
	for (unsigned i = 0; i < indices.size() / 3; i++) {
		unsigned a = indices[i * 3];
		unsigned b = indices[i * 3 + 1];
		unsigned c = indices[i * 3 + 2];

		glm::vec3 faceVector = glm::cross(vertices[c].Position - vertices[a].Position, vertices[b].Position - vertices[a].Position);

		vertices[a].Normal += faceVector;
		vertices[b].Normal += faceVector;
		vertices[c].Normal += faceVector;
	}

	// Normalize vectors
	for (unsigned i = 0; i < vertices.size(); i++) {
		vertices[i].Normal = glm::normalize(vertices[i].Normal);
	}

	// Bind the Vertex Array Object 
	glBindVertexArray(VAO);

	// Update vertices coords
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);
}