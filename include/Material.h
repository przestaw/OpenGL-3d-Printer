#pragma once

#include "Texture.h"
#include "shprogram.h"

class Material {
public:
  Material(const GLfloat shininess = 32.0f);
  Material(const Texture& texture, const GLfloat impact,
           GLfloat shininess = 32.0f);
  Material(const GLfloat shininess, const Texture& diffuseMap,
           const GLfloat diffuseImpact, const Texture& specularMap,
           const GLfloat specularImpact);
  Material(const Material& other);

  void draw(const ShaderProgram& shader);

  Texture getDiffuseMap();
  void setDiffuseMap(const Texture& map, const GLfloat impact);

  Texture getSpecularMap();
  void setSpecularMap(const Texture& map, const GLfloat impact);

  GLfloat getShininess();
  void setShininess(const GLfloat shininess);

private:
  Texture diffuseMap;
  Texture specularMap;
  GLfloat diffuseImpact{0.0};
  GLfloat specularImpact{0.0};
  GLfloat shininess{32.0};
};
