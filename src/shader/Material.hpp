#ifndef SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SHADER_MATERIAL_HPP_
#define SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SHADER_MATERIAL_HPP_

#include <glm/glm.hpp>

class Material
{
public:
  Material(glm::vec3 color);

  Material(const Material &other) = delete;
  Material(Material &&other) = delete;

  virtual ~Material();

  Material& operator=(const Material &other) = delete;
  Material& operator=(Material &&other) = delete;

  glm::vec3 ambient, diffuse, specular;

  float shininess;
};

#endif /* SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SHADER_MATERIAL_HPP_ */
