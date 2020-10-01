#include "LightManager.h"

LightManager::LightManager(int maxPointLightAmount, int maxSpotLightAmount)
    : maxPointLightAmount(maxPointLightAmount),
      maxSpotLightAmount(maxSpotLightAmount) {
  directionalLight = std::make_shared<DirectionalLight>();
  directionalLight->setUniformName("directionalLight");
}

void LightManager::setUpLight(const ShaderProgram& shaderProgram) {
  // Set up all light's data in shader
  setUpDirectionalLight(shaderProgram);
  setUpPointLights(shaderProgram);
  setUpSpotLights(shaderProgram);

  // Tell shader how many elemnts from array it should access
  shaderProgram.setIntUniform("amountOfPointLights", pointLightsVector.size());
  shaderProgram.setIntUniform("amountOfSpotLights", spotLightsVector.size());
}

std::shared_ptr<DirectionalLight> LightManager::getDirectionalLight() {
  return directionalLight;
}

void LightManager::addPointLight(std::shared_ptr<PointLight> light) {
  if (pointLightsVector.size() >= maxPointLightAmount) {
    std::cout << "Light was not added as there is no more room";
    return;
  }
  pointLightsVector.push_back(light);
  fixNames(LightType::POINT);
}

std::shared_ptr<PointLight> LightManager::addPointLight() {
  if (pointLightsVector.size() >= maxPointLightAmount) {
    std::cout << "Light was not added as there is no more room";
    return std::shared_ptr<PointLight>();
  }

  std::shared_ptr<PointLight> newPointLight = std::make_shared<PointLight>();
  pointLightsVector.push_back(newPointLight);
  fixNames(LightType::POINT);
  return newPointLight;
}

std::shared_ptr<PointLight> LightManager::getPointLight(const int index) {
  // TODO Maybe add try check or something?
  return pointLightsVector.at(index);
}

void LightManager::removePointLight(std::shared_ptr<PointLight> lightToRemove) {
  for (auto i = pointLightsVector.begin(); i != pointLightsVector.end(); ++i) {
    if (*i == lightToRemove) {
      pointLightsVector.erase(i);
      break;
    }
  }
  fixNames(LightType::POINT);
}

void LightManager::addSpotLight(std::shared_ptr<SpotLight> light) {
  if (spotLightsVector.size() >= maxSpotLightAmount) {
    std::cout << "New spot light was not added as there is no more room";
    return;
  }
  spotLightsVector.push_back(light);
  fixNames(LightType::SPOT);
}

std::shared_ptr<SpotLight> LightManager::addSpotLight() {
  if (spotLightsVector.size() >= maxSpotLightAmount) {
    std::cout << "Light was not added as there is no more room";
    return std::shared_ptr<SpotLight>();
  }

  std::shared_ptr<SpotLight> newSpotLight = std::make_shared<SpotLight>();
  spotLightsVector.push_back(newSpotLight);
  fixNames(LightType::SPOT);
  return newSpotLight;
}

std::shared_ptr<SpotLight> LightManager::getSpotLight(const int index) {
  // TODO Maybe add try check or something?
  return spotLightsVector.at(index);
}

void LightManager::removeSpotLight(std::shared_ptr<SpotLight> lightToRemove) {
  for (auto i = spotLightsVector.begin(); i != spotLightsVector.end(); ++i) {
    if (*i == lightToRemove) {
      spotLightsVector.erase(i);
      break;
    }
  }
  fixNames(LightType::SPOT);
}

void LightManager::fixNames(LightType lightType) {
  if (lightType == LightType::POINT) {
    for (unsigned int i = 0; i < pointLightsVector.size(); ++i) {
      auto light = pointLightsVector[i];
      light->setUniformName(
          std::string("pointLights[" + std::to_string(i) + "]"));
    }
  } else if (lightType == LightType::SPOT) {
    for (unsigned int i = 0; i < spotLightsVector.size(); ++i) {
      auto light = spotLightsVector[i];
      light->setUniformName(
          std::string("spotLights[" + std::to_string(i) + "]"));
    }
  }
}

// NOTE
// I am thinking if it actually reads good or if it could be rearranged
// If I forget to ask please let me know what do you
// ~saksamit2

void LightManager::setUpDirectionalLight(const ShaderProgram& shaderProgram) {
  shaderProgram.setVec3Uniform(directionalLight->getUniformName()
                                   + ".direction",
                               directionalLight->getDirection());

  shaderProgram.setVec3Uniform(directionalLight->getUniformName()
                                   + ".ambientStrength",
                               directionalLight->getAmbientStrength());

  shaderProgram.setVec3Uniform(directionalLight->getUniformName()
                                   + ".diffuseStrength",
                               directionalLight->getDiffuseStrength());

  shaderProgram.setVec3Uniform(directionalLight->getUniformName()
                                   + ".specularStrength",
                               directionalLight->getSpecularStrength());
}

void LightManager::setUpPointLights(const ShaderProgram& shaderProgram) {
  for (auto light : pointLightsVector) {
    shaderProgram.setVec3Uniform(light->getUniformName() + ".position",
                                 light->getPosition());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".ambientStrength",
                                 light->getAmbientStrength());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".diffuseStrength",
                                 light->getDiffuseStrength());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".specularStrength",
                                 light->getSpecularStrength());
    shaderProgram.setFloatUniform(light->getUniformName()
                                      + ".constantParameter",
                                  light->getConstantParameter());
    shaderProgram.setFloatUniform(light->getUniformName() + ".linearParameter",
                                  light->getLinearParameter());
    shaderProgram.setFloatUniform(light->getUniformName()
                                      + ".quadraticParameter",
                                  light->getQuadraticParameter());
  }
}

// NOTE It basically shares more than half of the code with method above
// How could I rewrite it so it won't duplicate as much code but still be
// readable? Or it is okay the way it is?
void LightManager::setUpSpotLights(const ShaderProgram& shaderProgram) {
  for (auto light : spotLightsVector) {
    shaderProgram.setVec3Uniform(light->getUniformName() + ".position",
                                 light->getPosition());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".direction",
                                 light->getDirection());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".ambientStrength",
                                 light->getAmbientStrength());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".diffuseStrength",
                                 light->getDiffuseStrength());
    shaderProgram.setVec3Uniform(light->getUniformName() + ".specularStrength",
                                 light->getSpecularStrength());
    shaderProgram.setFloatUniform(light->getUniformName()
                                      + ".constantParameter",
                                  light->getConstantParameter());
    shaderProgram.setFloatUniform(light->getUniformName() + ".linearParameter",
                                  light->getLinearParameter());
    shaderProgram.setFloatUniform(light->getUniformName()
                                      + ".quadraticParameter",
                                  light->getQuadraticParameter());
    shaderProgram.setFloatUniform(light->getUniformName() + ".cutOff",
                                  light->getCutOff());
    shaderProgram.setFloatUniform(light->getUniformName() + ".outerCutOff",
                                  light->getOuterCutOff());
  }
}
