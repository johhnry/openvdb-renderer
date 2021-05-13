#ifndef OPENVDB_RENDERER_SRC_UTILS_FILEUTILS_HPP_
#define OPENVDB_RENDERER_SRC_UTILS_FILEUTILS_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "log/Log.hpp"


namespace FileUtils {

  inline std::string readFile(const char *filePath) {
    // Retrieve the vertex/fragment source code from filePath
    std::string fileSource;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
      file.open(filePath);

      std::stringstream fileStream;

      // read file’s buffer contents into streams
      fileStream << file.rdbuf();

      // close file handlers
      file.close();

      // convert stream into string
      fileSource = fileStream.str();
    } catch (const std::ifstream::failure &e) {
      Log::error("Couldn't read shader file " + std::string(filePath));
      exit(EXIT_FAILURE);
    }

    return fileSource;
  }

} // namespace FileUtils

#endif /* OPENVDB_RENDERER_SRC_UTILS_FILEUTILS_HPP_ */
