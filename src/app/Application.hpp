#ifndef OPENVDB_RENDERER_SRC_APP_APPLICATION_HPP_
#define OPENVDB_RENDERER_SRC_APP_APPLICATION_HPP_

#include <string>

#include <GL/glew.h>
#include <imgui/imfilebrowser.h>
#include <openvdb/openvdb.h>

#include "vdb/VDBFile.hpp"
#include "app/ApplicationWindow.hpp"

#include "geometry/IGeometry.hpp"
#include "scene/Camera.hpp"
#include "scene/Light.hpp"

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
  void drawObjects();

  void loadVDBFile(std::string filename);

private:
  ApplicationWindow window;

  // UI options
  bool isWireframe = false;
  bool turnAnimation = true;
  float voxelSize = 0.1;
  float camCenterX = 0.0;
  float camCenterY = 0.0;
  float camCenterZ = 0.0;
  float angleOfView = 45;
  float turnAngle = 0;
  float distance = 5.0;

  Camera camera;
  Light light;

  // GUI
  ImGui::FileBrowser vdbFileDialog;

  std::unique_ptr<VDBFile> vdbFile;
  int previousGridIndex = 0;
  int currentGridIndex = 0;
};

#endif /* OPENVDB_RENDERER_SRC_APP_APPLICATION_HPP_ */
