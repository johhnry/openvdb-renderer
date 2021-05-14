#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 u, float f) : position(pos), lookAt(look), up(u), fov(f)
{
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() const
{
  return glm::lookAt(position, lookAt, up);
}

float Camera::getFOV() const
{
  return fov;
}

glm::vec3 Camera::getPosition() const
{
  return position;
}

glm::vec3 Camera::getUp() const { return up; }

glm::vec3 Camera::getDirection() const
{
  return glm::normalize(position - lookAt);
}

glm::vec3 Camera::getRight() const
{
  return glm::normalize(glm::cross(up, getDirection()));
}
