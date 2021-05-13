#ifndef OPENVDB_RENDERER_SRC_SHADER_ISHADER_HPP_
#define OPENVDB_RENDERER_SRC_SHADER_ISHADER_HPP_

#include <string>

#include "GL/glew.h"

class IShader
{
public:
  IShader(const IShader &other) = delete;
  IShader(IShader &&other) noexcept = delete;
  IShader& operator=(const IShader &other) = delete;
  IShader& operator=(IShader &&other) noexcept = delete;

  virtual ~IShader() noexcept;

public:
  GLuint getId() const;
  void compile();

protected:
  GLuint id;

  // Protected constructor to protect instantiation
  IShader(GLuint shaderType, const char *filePath);

private:
  GLuint shaderType;
  const char *filePath;

  std::string withShaderId(std::string msg) const;
};

#endif /* OPENVDB_RENDERER_SRC_SHADER_ISHADER_HPP_ */
