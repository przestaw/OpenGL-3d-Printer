#pragma once

#include "AbstractObj.h"
#include "Vertex.h"

#include <vector>

class GraphicsObj : public AbstractObj {
public:

	~GraphicsObj(){
		// Properly de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Draw(ShaderProgram shader){
		// Move object to desired place using AbstractObj model
		shader.setMat4Uniform("model", model); 
		//TEXTURE ??
		
		// Bind the Vertex Array Object
		glBindVertexArray(VAO);
		// Draw Object
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		// Unbind VAO
		glBindVertexArray(0);
	}

protected:
	// Vertex Array Object
	GLuint VAO;
	// Triangles and Indices, vector allows for easy modification
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	// Texture ??

	GraphicsObj() {
		// Generate buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	void setVertices(std::vector<Vertex> v) {
		// Assign Vertices
		vertices = v;
		vertices.shrink_to_fit();

		// Bind the Vertex Array Object first
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		// Color attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

		// Texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		glEnableVertexAttribArray(2);

		// Normal attribute
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(3);

		// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
		glBindVertexArray(0);
	}

	void setIndices(std::vector<unsigned int> i) {
		// Assign indices
		indices = i;
		indices.shrink_to_fit();

		// Bind the Vertex Array Object 
		glBindVertexArray(VAO);

		// Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// Unbind VAO
		glBindVertexArray(0);
	}

	void recalculateNormales() {
		// Zero all normales
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].Normal = glm::vec3(0.0f);
		}

		// Calc normales for faces and add to vertices
		for (int i = 0; i < indices.size() / 3; i++) {
			int a = indices[i * 3];
			int b = indices[i * 3 + 1];
			int c = indices[i * 3 + 2];

			glm::vec3 faceVector = glm::cross(vertices[c].Position - vertices[a].Position, vertices[b].Position - vertices[a].Position);

			vertices[a].Normal += faceVector;
			vertices[b].Normal += faceVector;
			vertices[c].Normal += faceVector;
		}

		// Normalize vectors
		for (int i = 0; i < vertices.size(); i++) {
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

private:
	// Vertex Buffer Object 
	GLuint VBO, 
	//and Element Buffer Object
			   EBO;
};