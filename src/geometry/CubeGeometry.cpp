#include "CubeGeometry.hpp"
#include "geometry/IGeometry.hpp"
#include "geometry/VAO.hpp"

CubeGeometry::CubeGeometry(float x, float y, float z, float sc)
  : IGeometry(x, y, z)
{
  vao.createCube(0, 0, 0, 1);
  scale = glm::vec3(sc);
  vao.commit();
}

CubeGeometry::~CubeGeometry() {}
