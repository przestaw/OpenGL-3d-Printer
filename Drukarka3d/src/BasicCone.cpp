#include "../include/BasicCone.h"

BasicCone::BasicCone(glm::vec3 baseColor, GLfloat height, GLfloat bottomRadius, GLfloat topRadius, unsigned nbSides)
	: height(height), bottomRadius(bottomRadius), topRadius(topRadius), nbSides(nbSides) {

	// Calculate Vertices and Triangles
	std::vector<glm::vec3> v = vertices();
	std::vector<GLuint>  t = triangles();
	std::vector<Vertex> vertices;

	// Assign base color to items 
	for (unsigned i = 0; i < v.size(); i++) {
		vertices.push_back(Vertex(v[i], baseColor, glm::vec2(0.0f), glm::vec3(0.0f)));
	}

	// Set Vertices and Calc Normales
	setVertices(vertices);
	setIndices(t);
	recalculateNormales();
}

std::vector<glm::vec3> BasicCone::vertices() {
	std::vector<glm::vec3> vertices;
	unsigned vert = 0;

	// Bottom cap
	vertices.push_back(glm::vec3(0.0, -height / 2.0f, 0.0));
	if (bottomRadius > 0) {
		for (vert = 0; vert < nbSides; vert++) {
			GLfloat rad = vert / (GLfloat)nbSides * _2pi;
			vertices.push_back(glm::vec3(cos(rad) * bottomRadius, -height / 2.0f, sin(rad) * bottomRadius));
		}
	}

	// Top cap
	vertices.push_back(glm::vec3(0.0, height / 2.0f, 0.0));
	if (topRadius > 0) {
		for (vert = 0; vert < nbSides; vert++) {
			GLfloat rad = vert / (GLfloat)nbSides * _2pi;
			vertices.push_back(glm::vec3(cos(rad) * topRadius, height / 2.0f, sin(rad) * topRadius));
		}
	}

	return vertices;
}

std::vector<GLuint> BasicCone::triangles() {
	std::vector<GLuint> triangles;

	// Bottom cap
	if (bottomRadius > 0) {
		for (unsigned i = 0; i < nbSides; i++) {
			triangles.push_back(0);
			triangles.push_back(((i + 1) % nbSides) + 1);
			triangles.push_back((i % nbSides) + 1);
		}
	}

	// Top cap
	if (topRadius > 0) {
		unsigned firstIdx = bottomRadius > 0 ? nbSides + 1 : 1;
		for (unsigned i = 0; i < nbSides; i++) {
			triangles.push_back(firstIdx);
			triangles.push_back((i % nbSides) + firstIdx + 1);
			triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
		}
	}

	// Sides 
	if (topRadius > 0 && bottomRadius > 0) {
		for (unsigned i = 0; i < nbSides; i++) {
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
		unsigned firstIdx = 1;
		for (unsigned i = 0; i < nbSides; i++) {
			triangles.push_back(0);
			triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
			triangles.push_back((i % nbSides) + firstIdx + 1);
		}
	}
	else if (bottomRadius > 0) {
		unsigned firstIdx = 0;
		for (unsigned i = 0; i < nbSides; i++) {
			triangles.push_back((i % nbSides) + firstIdx + 1);
			triangles.push_back(((i + 1) % nbSides) + firstIdx + 1);
			triangles.push_back(nbSides + 1);
		}
	}

	return triangles;
}