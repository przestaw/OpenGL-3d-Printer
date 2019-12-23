#pragma once

#include "GraphicsObj.h"
#include <cmath>
#define M_PI 3.14159265358979323846


class BasicCone : public GraphicsObj {
public:
	BasicCone(glm::vec3 baseColor, GLfloat height, GLfloat bottomRadius, GLfloat topRadius = 0, int nbSides = 32) {
		this->height = height;
		this->bottomRadius = bottomRadius;
		this->topRadius = topRadius;
		this->nbSides = nbSides;

		std::vector<glm::vec3> v = vertices();
		std::vector<GLuint>  t = triangles();
		std::vector<Vertex> vertices;

		for (int i = 0; i < v.size(); i++) {
			vertices.push_back(Vertex(v[i], baseColor, glm::vec2(0.0f), glm::vec3(0.0f)));
		}

		setVertices(vertices);
		setIndices(t);
		recalculateNormales();
	}
	~BasicCone() {}

private:
	int nbSides;
	GLfloat height;
	GLfloat bottomRadius;
	GLfloat topRadius;

	std::vector<glm::vec3> vertices() {
		std::vector<glm::vec3> vertices;
		int vert = 0;

		GLfloat _2pi = M_PI * 2.0f;

		// Bottom cap
		vertices.push_back(glm::vec3(0.0, -height / 2.0f, 0.0));
		if (bottomRadius > 0) {
			for (vert = 0; vert < nbSides; vert++) {
				float rad = vert / (float)nbSides * _2pi;
				vertices.push_back(glm::vec3(cos(rad) * bottomRadius, -height / 2.0f, sin(rad) * bottomRadius));
			}
		}


		// Top cap
		vertices.push_back(glm::vec3(0.0, height / 2.0f, 0.0));
		if (topRadius > 0) {
			for (vert = 0; vert < nbSides; vert++) {
				float rad = vert / (float)nbSides * _2pi;
				vertices.push_back(glm::vec3(cos(rad) * topRadius, height / 2.0f, sin(rad) * topRadius));
			}
		}

		return vertices;
	}

	std::vector<GLuint> triangles() {
		std::vector<GLuint> triangles;

		// Bottom cap
		if (bottomRadius > 0) {
			for (int i = 0; i < nbSides; i++) {
				triangles.push_back(0);
				triangles.push_back(((i + 1) % nbSides) + 1);
				triangles.push_back((i % nbSides) + 1);
			}
		}

		// Top cap
		if (topRadius > 0) {
			int firstIdx = bottomRadius > 0 ? nbSides + 1 : 1;
			for (int i = 0; i < nbSides; i++) {
				triangles.push_back(firstIdx);
				triangles.push_back((i % nbSides) + firstIdx + 1);
				triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
			}
		}

		// Sides 
		if (topRadius > 0 && bottomRadius > 0) {
			for (int i = 0; i < nbSides; i++) {
				std::vector<unsigned> tri = quadToTri(
					(i % nbSides) + 1,
					((i + 1) % nbSides) + 1,
					((i + 1) % nbSides) + 1 + nbSides + 1,
					(i % nbSides) + 1 + nbSides + 1
				);
				triangles.insert(triangles.end(), tri.begin(), tri.end());
			}
		}
		else if (topRadius > 0) {
			int firstIdx = 1;
			for (int i = 0; i < nbSides; i++) {
				triangles.push_back(0);
				triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
				triangles.push_back((i % nbSides) + firstIdx + 1);
			}
		}
		else if (bottomRadius > 0) {
			int firstIdx = 0;
			for (int i = 0; i < nbSides; i++) {
				triangles.push_back((i % nbSides) + firstIdx + 1);
				triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
				triangles.push_back(nbSides + 1);
			}
		}

		return triangles;
	}

	std::vector<GLuint> quadToTri(GLuint a, GLuint b, GLuint c, GLuint d) {
		return { a, b, c, c, d, a };
	}
};