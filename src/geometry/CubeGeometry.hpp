#ifndef OPENVDB_RENDERER_SRC_GEOMETRY_CUBEGEOMETRY_HPP_
#define OPENVDB_RENDERER_SRC_GEOMETRY_CUBEGEOMETRY_HPP_

#include "IGeometry.hpp"

class CubeGeometry : public IGeometry
{
public:
  CubeGeometry(float x, float y, float z, float scale = 1);

  CubeGeometry(const CubeGeometry &other);
  CubeGeometry(CubeGeometry &&other) noexcept;

  virtual ~CubeGeometry() noexcept;

  CubeGeometry& operator=(const CubeGeometry &other) = delete;
  CubeGeometry& operator=(CubeGeometry &&other) = delete;
};

#endif /* OPENVDB_RENDERER_SRC_GEOMETRY_CUBEGEOMETRY_HPP_ */
