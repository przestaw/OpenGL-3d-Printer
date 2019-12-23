#pragma once

#include "AbstractObj.h"
#include "Vertex.h"

#include <vector>

class GraphicsObj : public AbstractObj {
public:

	~GraphicsObj(){
		//not sure if it is nesessary
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Draw(ShaderProgram shader){
		//move object to desired place using AbstractObj model
		shader.setMat4Uniform("model", model); 
		//TEXTURE ??
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

protected:
	GLuint VAO;
	std::vector<Vertex> vertices;
	//Texture ??
	std::vector<GLuint> indices;

	GraphicsObj() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	void setVertices(std::vector<Vertex> v) {
		vertices = v;

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glBindVertexArray(0);
	}

	void setIndices(std::vector<unsigned int> i) {
		indices = i;

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	void recalculateNormales() {
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].Normal = glm::vec3(0.0f);
		}

		for (int i = 0; i < indices.size() / 3; i++) {
			int a = indices[i * 3];
			int b = indices[i * 3 + 1];
			int c = indices[i * 3 + 2];

			glm::vec3 faceVector = glm::cross(vertices[c].Position - vertices[a].Position, vertices[b].Position - vertices[a].Position);

			vertices[a].Normal += faceVector;
			vertices[b].Normal += faceVector;
			vertices[c].Normal += faceVector;
		}

		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].Normal = glm::normalize(vertices[i].Normal);
		}

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

private:
	GLuint VBO, EBO;
};