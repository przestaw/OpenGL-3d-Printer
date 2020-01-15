#include "DeciduousTree.h"
#include <random>
#include <BasicCone.h>


DeciduousTree::DeciduousTree(glm::vec3 leaves, Texture leaves_tex, glm::vec3 wood, Texture wood_tex, GLfloat height, GLfloat radius, GLuint segments) {
	std::mt19937_64 myRand(std::random_device{}());
	std::uniform_real_distribution<GLfloat> myRandFloat(-0.7 * radius, 0.7 * radius);
}
