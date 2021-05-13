#include <sstream>
#include <string>

#include <GLFW/glfw3.h>

#include "Log.hpp"

// Static members
int Log::nbMessages = 0;
int Log::nbErrors = 0;

int Log::level = 3;

std::string Log::withColor(std::string text, LogColor color)
{
  std::ostringstream stream;
  stream << "\033[" << static_cast<int>(color) << "m" << text << "\033[0m";
  return stream.str();
}

void Log::message(std::string message)
{
  std::ostringstream msg;
  msg << "LOG     [" << (nbMessages++) << "] -\t" << message;
  if (Log::level >= 2) std::cout << withColor(msg.str(), LogColor::Yellow) << std::endl;
}

void Log::success(std::string message) {
  std::ostringstream msg;
  msg << "SUCCESS [" << (nbMessages++) << "] -\t" << message;
  if (Log::level >= 1) std::cout << withColor(msg.str(), LogColor::Green) << std::endl;
}

void Log::info(std::string message) {
  std::ostringstream msg;
  msg << "INFO    [" << (nbMessages++) << "] -\t" << message;
  if (Log::level >= 3) std::cout << withColor(msg.str(), LogColor::Blue) << std::endl;
}

void Log::error(std::string error)
{
  std::ostringstream err;
  err << "ERROR   [" << (nbErrors++) << "] -\t" << error;
  std::cerr << withColor(err.str(), LogColor::Red) << std::endl;
}

void Log::errorCallBack(int error, const char *description)
{
  std::ostringstream text;
  text << "Code : " << error << ", " << description;
  Log::error(text.str());
}
