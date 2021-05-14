#ifndef SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SCENE_CAMERA_HPP_
#define SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SCENE_CAMERA_HPP_

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
  Camera(glm::vec3 pos, glm::vec3 look = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 u = glm::vec3(0.f, 1.f, 0.0f), float f = 45.0f);

  virtual ~Camera();

  glm::mat4 getViewMatrix() const;
  float getFOV() const;
  glm::vec3 getPosition() const;
  glm::vec3 getUp() const;

  glm::vec3 getDirection() const;
  glm::vec3 getRight() const;

  glm::vec3 position;
  glm::vec3 lookAt;

private:
  glm::vec3 up;
  float fov;
};

#endif /* SIMPLE_OPENGL_ENGINE_SRC_OPENGL_SCENE_CAMERA_HPP_ */
