#ifndef OPENVDB_RENDERER_SRC_GEOMETRY_IGEOMETRY_HPP_
#define OPENVDB_RENDERER_SRC_GEOMETRY_IGEOMETRY_HPP_

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>

#include "geometry/VAO.hpp"
#include "shader/Material.hpp"
#include "shader/Program.hpp"

class IGeometry
{
public:
  IGeometry(float x, float y, float z);

  IGeometry(const IGeometry &other);
  IGeometry(IGeometry &&other) = delete;

  virtual ~IGeometry();

  IGeometry& operator=(const IGeometry &other) = delete;
  IGeometry& operator=(IGeometry &&other) = delete;

  void draw(Program &displayProgram);

  glm::vec3 getPosition() const;
  glm::quat getRotation() const;
  glm::vec3 getUp() const;
  glm::vec3 getRight() const;

  // void setShader(std::shared_ptr<Shader> sh);
  void setMaterial(std::shared_ptr<Material> mat);

  void setColor(float r, float g, float b);
  void setColorRGB(float r, float g, float b);

  void setScale(float scale);

  void rotate(float angle, glm::vec3 axis);

protected:
  VAO vao;
  // std::shared_ptr<Shader> shader;
  std::shared_ptr<Material> material;

  glm::vec3 position, scale;
  glm::quat rotation;
  glm::vec3 color;
};

#endif /* OPENVDB_RENDERER_SRC_GEOMETRY_IGEOMETRY_HPP_ */
