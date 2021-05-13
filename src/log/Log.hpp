#ifndef OPENVDB_RENDERER_SRC_LOG_LOG_HPP_
#define OPENVDB_RENDERER_SRC_LOG_LOG_HPP_

#include <iostream>

// ANSI escape color codes
enum class LogColor { Red = 31, Yellow = 33, Green = 32, Blue = 35};

class Log
{
public:
  Log();

  Log(const Log &other) = delete;
  Log(Log &&other) = delete;
  Log& operator=(const Log &other) = delete;
  Log& operator=(Log &&other) = delete;

  virtual ~Log();

public:
  static void message(std::string message);
  static void success(std::string message);
  static void info(std::string message);
  static void error(std::string error);
  static void errorCallBack(int error, const char *description);

  static int level;

private:
  static std::string withColor(std::string text, LogColor color);
  static int nbMessages, nbErrors;
};

#endif /* OPENVDB_RENDERER_SRC_LOG_LOG_HPP_ */
