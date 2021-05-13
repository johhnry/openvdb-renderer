#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include "log/Log.hpp"

#include "FragmentShader.hpp"


FragmentShader::FragmentShader(const char *filePath) :
  IShader(GL_FRAGMENT_SHADER, filePath)
{
}

FragmentShader::~FragmentShader() noexcept
{
  std::ostringstream address;
  address << this;
  Log::info("Destructor FragmentShader " + address.str());
}
