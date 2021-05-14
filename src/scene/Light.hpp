#ifndef SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SCENE_LIGHT_HPP_
#define SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SCENE_LIGHT_HPP_

#include <glm/glm.hpp>

class Light
{
public:
  Light(glm::vec3 pos);

  Light(const Light &other) = delete;
  Light(Light &&other) = delete;

  virtual ~Light();

  Light& operator=(const Light &other) = delete;
  Light& operator=(Light &&other) = delete;

  glm::vec3 position;
  glm::vec3 ambient, diffuse, specular;
};

#endif /* SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SCENE_LIGHT_HPP_ */
