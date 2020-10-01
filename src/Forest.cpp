#include "Forest.h"
#include <BasicCone.h>
#include <BasicCuboid.h>
#include <iostream>
#include <random>

Forrest::Forrest(GLfloat centerR, GLfloat outerR, GLfloat maxHeight,
                 unsigned coniferCount, unsigned deciduousCount,
                 Material woodTex, Material deciduousGreen,
                 Material coniferGreen, unsigned iceCreamCount) {
  std::mt19937_64 myRand(std::random_device{}());
  std::uniform_real_distribution<GLfloat> myRandFloat(centerR, outerR);
  std::normal_distribution<GLfloat> myRandHeight(0.0, 0.3 * maxHeight);

  for (unsigned i = 0; i < iceCreamCount; ++i) {
    GLfloat moveX = myRandFloat(myRand);
    GLfloat moveY = myRandFloat(myRand);

    moveX = myRand() % 2 == 1 ? moveX : -moveX;
    moveY = myRand() % 2 == 0 ? moveY : -moveY;

    GLfloat height = 1.6 * maxHeight - abs(myRandHeight(myRand));

    IceCream ice1(abs(height));
    ice1.translate(glm::vec3(moveX, 0.0, moveY));

    this->copyObjects(ice1);
  }

  for (unsigned i = 0; i < 1 + coniferCount / 2; ++i) {
    GLfloat moveX = myRandFloat(myRand);
    GLfloat moveY = myRandFloat(myRand);

    moveX = myRand() % 2 == 1 ? moveX : -moveX;
    moveY = myRand() % 2 == 0 ? moveY : -moveY;

    GLfloat height    = 1.9 * maxHeight - abs(myRandHeight(myRand));
    GLfloat radius    = maxHeight * 0.8 - abs(myRandHeight(myRand)) * 0.4;
    unsigned segments = 5 + myRand() % 6;

    ConiferTree tree(glm::vec3(0.1, 0.99, 0.3), glm::vec3(0.3, 0.18, 0.1),
                     abs(height), abs(radius), segments, coniferGreen, woodTex);
    tree.translate(glm::vec3(moveX, 0.0, moveY));

    this->copyObjects(tree);
  }

  for (unsigned i = 0; i < 1 + coniferCount / 2; ++i) {
    GLfloat moveX = myRandFloat(myRand);
    GLfloat moveY = myRandFloat(myRand);

    moveX = myRand() % 2 == 1 ? moveX : -moveX;
    moveY = myRand() % 2 == 0 ? moveY : -moveY;

    GLfloat height    = 1.5 * maxHeight - abs(myRandHeight(myRand));
    GLfloat radius    = maxHeight * 0.9 - abs(myRandHeight(myRand)) * 0.4;
    unsigned segments = 2 + myRand() % 5;

    ConiferTree tree(glm::vec3(0.1, 0.7, 0.5), glm::vec3(0.3, 0.18, 0.1),
                     abs(height), abs(radius), segments, coniferGreen, woodTex);
    tree.translate(glm::vec3(moveX, 0.0, moveY));

    this->copyObjects(tree);
  }

  for (unsigned i = 0; i < 1 + deciduousCount / 2; ++i) {
    GLfloat moveX = myRandFloat(myRand);
    GLfloat moveY = myRandFloat(myRand);

    moveX = myRand() % 2 == 1 ? moveX : -moveX;
    moveY = myRand() % 2 == 0 ? moveY : -moveY;

    GLfloat height    = 2 * maxHeight - abs(myRandHeight(myRand));
    GLfloat radius    = 1.45 * maxHeight - abs(myRandHeight(myRand));
    unsigned segments = 2 + myRand() % 6;

    DeciduousTree tree(glm::vec3(0.7, 0.3, 0.0), glm::vec3(0.35, 0.18, 0.15),
                       abs(height), abs(radius), segments, deciduousGreen,
                       woodTex);
    tree.translate(glm::vec3(moveX, 0.0, moveY));

    this->copyObjects(tree);
  }

  for (unsigned i = 0; i < 1 + deciduousCount / 2; ++i) {
    GLfloat moveX = myRandFloat(myRand);
    GLfloat moveY = myRandFloat(myRand);

    moveX = myRand() % 2 == 1 ? moveX : -moveX;
    moveY = myRand() % 2 == 0 ? moveY : -moveY;

    GLfloat height    = 2.3 * maxHeight - abs(myRandHeight(myRand));
    GLfloat radius    = 1.2 * maxHeight - abs(myRandHeight(myRand));
    unsigned segments = 3 + myRand() % 5;

    DeciduousTree tree(glm::vec3(0.3, 0.6, 0.0), glm::vec3(0.35, 0.2, 0.1),
                       abs(height), abs(radius), segments, deciduousGreen,
                       woodTex);
    tree.translate(glm::vec3(moveX, 0.0, moveY));

    this->copyObjects(tree);
  }
}
