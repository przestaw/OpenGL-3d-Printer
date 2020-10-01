#include "DeciduousTree.h"
#include <BasicCone.h>
#include <BasicSphere.h>
#include <CompositeGroup.h>
#include <random>

DeciduousTree::DeciduousTree(glm::vec3 leaves, glm::vec3 wood, GLfloat height,
                             GLfloat radius, GLuint segments,
                             Material leavesTex, Material woodTex) {
  std::mt19937_64 myRand(std::random_device{}());
  std::uniform_real_distribution<GLfloat> myRandFloat(0.24, 1.);
  BasicCone woodCyl(wood, height * 0.8, radius * 0.35, radius * 0.2);

  woodCyl.translate(glm::vec3(0.0, -height * 0.5, 0.0));
  woodCyl.setMaterial(woodTex);

  this->addObject(woodCyl);

  GLfloat step = height / (segments * 1.5);
  radius       = radius / 2.8;
  CompositeGroup green;
  BasicSphere bot(leaves, radius);
  green.addObject(bot);

  for (unsigned i = 0; i < segments; ++i) {
    unsigned j = i <= (segments / 2) ? i : ((segments - i) / 2);
    ++j;
    for (j *= 2; j > 0; --j) {
      GLfloat move = radius / (i + 2);
      BasicSphere sphere(leaves, radius * (0.8 + (segments - i) * 0.15), 24,
                         24);

      GLfloat moveX = myRandFloat(myRand) * move;
      GLfloat moveY = myRandFloat(myRand) * move;
      moveX         = myRand() % 2 == 1 ? moveX : -moveX;
      moveY         = myRand() % 2 == 1 ? moveY : -moveY;
      sphere.translate(glm::vec3(moveX, step * (i + 0.01 * j), moveY));
      green.addObject(sphere);
    }
  }

  BasicSphere top(leaves, radius, 24, 24);
  top.translate(glm::vec3(0.0, step * segments, 0.0));
  green.setMaterial(leavesTex);
  green.addObject(top);

  this->addObject(green);
  this->translate(glm::vec3(0.0, height * 0.8, 0.0));
}
