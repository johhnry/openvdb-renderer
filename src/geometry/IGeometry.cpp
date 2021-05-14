#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IGeometry.hpp"
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

IGeometry::IGeometry(float x, float y, float z) : position(x, y, z), scale(1.0), rotation(1, 0, 0, 0) {}

IGeometry::~IGeometry() {}

void IGeometry::draw(Program &displayProgram)
{
  glm::mat4 translate = glm::translate(glm::mat4(1.0), position);
  glm::mat4 rotate = glm::mat4_cast(rotation);
  glm::mat4 sc = glm::scale(glm::mat4(1.0), scale);
  displayProgram.setMat4("model", translate * rotate * sc);

  vao.bind();
  vao.draw();
  vao.unbind();
}

void IGeometry::rotate(float angle, glm::vec3 axis)
{
  rotation = rotation * glm::angleAxis(angle, axis);
}

glm::vec3 IGeometry::getPosition() const
{
  return position;
}

glm::quat IGeometry::getRotation() const
{
  return rotation;
}

glm::vec3 IGeometry::getUp() const
{
  return rotation * glm::vec3(0, 1, 0);
}

glm::vec3 IGeometry::getRight() const
{
  return rotation * glm::vec3(1, 0, 0);
}

void IGeometry::setScale(float scale)
{
  this->scale = glm::vec3(scale, scale, scale);
}

void IGeometry::setColor(float r, float g, float b)
{
  color = glm::vec3(r, g, b);
}

void IGeometry::setColorRGB(float r, float g, float b)
{
  setColor(r / 255.0, g / 255.0, b / 255.0);
}
