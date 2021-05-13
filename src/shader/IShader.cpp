#include "utils/FileUtils.hpp"

#include "IShader.hpp"
#include <string>


IShader::IShader(GLuint shaderType, const char *filePath) :
  shaderType(shaderType),
  filePath(filePath)
{
  // Read the source file
  Log::message("Reading shader file : " + std::string(filePath));

  std::string sourceFile = FileUtils::readFile(filePath);
  const char *shaderSource = sourceFile.c_str();

  // Create the shader
  id = glCreateShader(shaderType);

  Log::info(withShaderId("Created"));

  // Attach the source file to that shader
  glShaderSource(id, 1, &shaderSource, NULL);
}

IShader::~IShader() noexcept
{
  Log::info("Deleting shader...");
  glDeleteShader(this->id);
  std::ostringstream address;
  address << this;
  Log::info("Destructor Shader " + address.str());
}

std::string IShader::withShaderId(std::string msg) const {
  std::ostringstream stream;
  stream << "Shader [" + std::to_string(id) + "]: " + msg;
  return stream.str();
}

GLuint IShader::getId() const
{
  return id;
}

void IShader::compile()
{
  // Compile it
  glCompileShader(id);

  int success;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  // Check if compilation was successfull
  if (!success) {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    throw withShaderId("Compilation failed " + std::string(filePath) + ": " + std::string(infoLog));
  }

  Log::success(withShaderId("Compiled : " + std::string(filePath)));
}
