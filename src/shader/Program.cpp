#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "log/Log.hpp"

#include "Program.hpp"


Program::Program()
{
  this->id = glCreateProgram();
}

Program::~Program() noexcept
{
  Log::info("Deleting program...");
  glDeleteProgram(this->id);
  std::ostringstream address;
  address << this;
  Log::info("Destructor Program " + address.str());
}

GLuint Program::getId() const
{
  return id;
}

void Program::beginUse() const
{
  glUseProgram(id);
}

void Program::endUse() const
{
  glUseProgram(0);
}

std::string Program::withProgramId(std::string msg) const
{
  std::ostringstream stream;
  stream << "Program [" + std::to_string(id) + "]: " + msg;
  return stream.str();
}

void Program::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Program::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Program::setVec3(const char *name, float x, float y, float z) const
{
  glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Program::attachShader(const IShader &shader)
{
  glAttachShader(this->id, shader.getId());
  Log::success(withProgramId("Attached shader " + std::to_string(shader.getId())));
}

void Program::link()
{
  Log::message(withProgramId("Linking..."));
  glLinkProgram(id);

  int success;
  char infoLog[512];

  glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    throw withProgramId("Linking failed : " + std::string(infoLog));
  }

  Log::success(withProgramId("Linking successfull!"));
  std::cout << std::endl;
}
