#ifndef OPENVDB_RENDERER_SRC_PROGRAM_PROGRAM_HPP_
#define OPENVDB_RENDERER_SRC_PROGRAM_PROGRAM_HPP_

#include <string>

#include "GL/glew.h"

#include "shader/IShader.hpp"


class Program
{
public:
  Program();

  Program(const Program &other) = delete;
  Program(Program &&other) noexcept = delete;
  Program& operator=(const Program &other) = delete;
  Program& operator=(Program &&other) = delete;

  virtual ~Program() noexcept;

public:
  GLuint getId() const;

  void attachShader(const IShader &shader);
  void link();

  void beginUse() const;
  void endUse() const;

  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec3(const char *name, float x, float y, float z) const;

private:
  GLuint id;
  std::string withProgramId(std::string msg) const;
};

#endif /* OPENVDB_RENDERER_SRC_PROGRAM_PROGRAM_HPP_ */
