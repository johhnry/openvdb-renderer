#ifndef OPENVDB_RENDERER_SRC_APP_APPLICATION_HPP_
#define OPENVDB_RENDERER_SRC_APP_APPLICATION_HPP_

#include <openvdb/openvdb.h>
#include <imgui/imfilebrowser.h>
#include <vdb/VDBFile.hpp>

#include "app/ApplicationWindow.hpp"

class Application
{
public:
  Application();

  Application(const Application &other) = delete;
  Application(Application &&other) = delete;
  Application& operator=(const Application &other) = delete;
  Application& operator=(Application &&other) = delete;

  virtual ~Application() noexcept {};

public:
  void initializeGlfw(const uint32_t width, const uint32_t height);
  void initializeGlew();
  void initializeImGui();
  void initializeOpenVDB();

  void shutdownImGui();

  void printArguments(int argc, char **argv);

  void loop();
  int run(int argc, char *argv[]);
  void displayGUI();

private:
  ApplicationWindow window;

  // GUI
  ImGui::FileBrowser vdbFileDialog;

  std::unique_ptr<VDBFile> vdbFile;
  int previousGridIndex = 0;
  int currentGridIndex = 0;
};

#endif /* OPENVDB_RENDERER_SRC_APP_APPLICATION_HPP_ */
