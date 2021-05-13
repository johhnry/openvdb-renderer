#ifndef OPENVDB_RENDERER_SRC_GEOMETRY_FULLSCREENVAO_HPP_
#define OPENVDB_RENDERER_SRC_GEOMETRY_FULLSCREENVAO_HPP_

#include "GL/glew.h"

class FullScreenVAO
{
public:
  FullScreenVAO();

  FullScreenVAO(const FullScreenVAO &other) = delete;
  FullScreenVAO(FullScreenVAO &&other) noexcept = delete;
  FullScreenVAO& operator=(const FullScreenVAO &other) = delete;
  FullScreenVAO& operator=(FullScreenVAO &&other) = delete;

  virtual ~FullScreenVAO() noexcept {};

public:
  void bind() const;
  void unbind() const;

  void draw() const;

private:
  GLuint quadIBO, quadVBO, quadVAO;
};

#endif /* OPENVDB_RENDERER_SRC_GEOMETRY_FULLSCREENVAO_HPP_ */
