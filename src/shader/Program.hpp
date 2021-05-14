#ifndef OPENVDB_RENDERER_SRC_PROGRAM_PROGRAM_HPP_
#define OPENVDB_RENDERER_SRC_PROGRAM_PROGRAM_HPP_

#include "glm/glm.hpp"
#include <string>

#include "GL/glew.h"
#include "scene/Light.hpp"

#include "shader/IShader.hpp"

class Program {
public:
  Program();

  Program(const Program &other) = delete;
  Program(Program &&other) noexcept = delete;
  Program &operator=(const Program &other) = delete;
  Program &operator=(Program &&other) = delete;

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

  void setVec3(const char *name, glm::vec3 vec) const;
  void setMat4(const char *name, glm::mat4 matrix) const;

  void useLight(const Light &light);

private:
  GLuint id;
  std::string withProgramId(std::string msg) const;
};

#endif /* OPENVDB_RENDERER_SRC_PROGRAM_PROGRAM_HPP_ */
