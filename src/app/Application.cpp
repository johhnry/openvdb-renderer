#include <cstdlib>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include <openvdb/Grid.h>
#include <openvdb/io/File.h>
#include <string>
#include <unistd.h>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>

#include <imgui/imfilebrowser.h>

#include <openvdb/openvdb.h>

#include "utils/FileUtils.hpp"
#include "log/Log.hpp"

#include "shader/FragmentShader.hpp"
#include "shader/Program.hpp"
#include "shader/VertexShader.hpp"

#include "geometry/FullScreenVAO.hpp"

#include "Application.hpp"
#include <vector>

Application::Application()
    : window(), camera(glm::vec3(10.f, 10.f, 10.f)),
      light(glm::vec3(200.f, 200.f, -200.f)) {
  // Configure file dialog
  vdbFileDialog.SetTitle("Choose OpenVDB file");
  vdbFileDialog.SetTypeFilters({".vdb"});
}

void Application::initializeGlfw(const uint32_t width, const uint32_t height)
{
  int glfw = glfwInit();

  if (glfw != GLFW_TRUE) {
    throw "GLFW: Couldn't initialize correctly";
  }

  Log::success("GLFW: Successfully initialized");

  // Setting glfw callbacks for errors
  glfwSetErrorCallback(Log::errorCallBack);

  Log::message("GLFW: Running version " + std::string(glfwGetVersionString()));

  // OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Initialize window
  window.initialize("OpenVDB renderer", width, height);

  // Set frame interval swap
  glfwSwapInterval(1);

  // Enable depth
  glEnable(GL_DEPTH_TEST);

  // Enable multi sampling
  glfwWindowHint(GLFW_SAMPLES, 4);
  glEnable(GL_MULTISAMPLE);
}

void Application::initializeGlew()
{
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    std::string glfwError = std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
    throw "GLEW initialization error : " + glfwError;
  }

  std::string glewVersion = std::string(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION)));
  Log::success("Using GLEW: " + glewVersion);
}

void Application::initializeImGui()
{
  // Create context for glfw and opengl backends
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
  ImGui_ImplOpenGL3_Init();

  Log::success("Successfully initialized ImGui GLFW/OpenGL3 backends");
}

void Application::initializeOpenVDB()
{
  openvdb::initialize();
  Log::success("OpenVDB: initialized");
}

void Application::shutdownImGui()
{
  Log::message("Shuting down ImGui...");
  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
  Log::success("ImGui context destroyed");
}

void Application::printArguments(int argc, char **argv) {
  std::string args = "";
  for (int i = 0; i < argc; i++)
    args += std::string(argv[i]) + " ";
  Log::info("Command parameters (" + std::to_string(argc) + ") : " + args);
  std::cout << std::endl;
}

bool VectorOfStringGetter(void *data, int n, const char **out_text) {
  const std::vector<std::string> *v = (std::vector<std::string> *)data;
  *out_text = v->at(n).c_str();
  return true;
}

void Application::loadVDBFile(std::string filename)
{
  // Open VDB file
  vdbFile = std::make_unique<VDBFile>(filename);
  vdbFile->constructPointCloud(currentGridIndex);
}

void Application::displayGUI()
{
  // Create frames
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("OpenVDB control");

  if (ImGui::CollapsingHeader("VDB file", ImGuiTreeNodeFlags_DefaultOpen)) {
    // open file dialog when user clicks this button
    if (ImGui::Button("Import VDB file"))
      vdbFileDialog.Open();

    ImGui::Separator();

    // If VDB file was opened
    if (vdbFile) {
      // Display filename
      ImGui::Text("%s", ("File : " + vdbFile->filename).c_str());

      // Display grid names in a list box
      auto gridNames = vdbFile->getGridNames();
      ImGui::ListBox("Grids", &currentGridIndex, VectorOfStringGetter, (void*)&gridNames, (int)gridNames.size());

      // Display metadata table
      vdbFile->displayMetaData(currentGridIndex);
    }
  }

  if (ImGui::CollapsingHeader("Display options", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Checkbox("Wireframe", &isWireframe);
    ImGui::Checkbox("Turn animation", &turnAnimation);

    ImGui::Separator();

    ImGui::SliderFloat("Voxel size", &voxelSize, 0.0f, 0.5f);

    ImGui::Separator();

    ImGui::SliderFloat("Cam center X", &camCenterX, -10.0, 10.0);
    ImGui::SliderFloat("Cam center Y", &camCenterY, -10.0, 10.0);
    ImGui::SliderFloat("Cam center Z", &camCenterZ, -10.0, 10.0);

    ImGui::Separator();

    ImGui::SliderFloat("Angle of view", &angleOfView, 0.0, 360.0);
    ImGui::SliderFloat("Distance from center", &distance, 0.0, 50.0);
    ImGui::SliderFloat("Rotation", &turnAngle, 0.0, 360.0);
  }

    vdbFileDialog.Display();

  // File dialog selection
  if (vdbFileDialog.HasSelected()) {
    std::string filename = vdbFileDialog.GetSelected().string();
    Log::info("Selected filename : " + filename);

    // Load VDB file and construct geometry
    loadVDBFile(filename);

    vdbFileDialog.ClearSelected();
  }

  ImGui::End();

  // Render UI
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int Application::run(int argc, char **argv)
{
  printArguments(argc, argv);

  // ------------------------------------------
  // INITIALIZATION
  // ------------------------------------------
  try {
    initializeGlfw(1280, 720);
    initializeGlew();
    initializeImGui();
    initializeOpenVDB();
  } catch (const std::string &error) {
    Log::error(error);
    return EXIT_FAILURE;
  }

  Program displayProgram;

  try {
    // Vertex shader and fragment shader
    VertexShader vertexShader("../src/glsl/defaultShader.vert");
    FragmentShader fragmentShader("../src/glsl/defaultShader.frag");

    vertexShader.compile();
    fragmentShader.compile();

    displayProgram.attachShader(vertexShader);
    displayProgram.attachShader(fragmentShader);

    displayProgram.link();
  } catch (const std::string &error) {
    Log::error(error);
    return EXIT_FAILURE;
  }

  // ------------------------------------------
  // LOOP
  // ------------------------------------------
  while (!glfwWindowShouldClose(window.getGLFWwindow())) {
    // GLFW events and clear window
    glfwPollEvents();
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (isWireframe) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    double time = glfwGetTime() / 2.0;

    // Move camera
    camera.lookAt = glm::vec3(camCenterX, camCenterY, camCenterZ);
    float radius = distance * std::cos(glm::radians(angleOfView));
    float h = distance * std::sin(glm::radians(angleOfView));

    float angle = turnAnimation ? time : glm::radians(turnAngle);
    camera.position = glm::vec3(std::cos(angle) * radius, h, std::sin(angle) * radius);

    // If vdb file, display it
    if (vdbFile) {
      displayProgram.beginUse();

      displayProgram.useLight(light);
      displayProgram.setVec3("viewPos", camera.getPosition());

      // Set material properties
      displayProgram.setVec3("material.ambient", glm::vec3(1.0f));
      displayProgram.setVec3("material.diffuse", glm::vec3(0.1f, 0.4f, 1.0f));
      displayProgram.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
      displayProgram.setFloat("material.shininess", 32.f);

      // Compute view matrices
      glm::mat4 projection = glm::perspective(
          glm::radians(camera.getFOV()),
          float(window.getWidth()) / float(window.getHeight()), 0.1f, 100.0f);
      glm::mat4 view = camera.getViewMatrix();

      displayProgram.setMat4("projection", projection);
      displayProgram.setMat4("view", view);

      // Display vdb
      vdbFile->draw(displayProgram, voxelSize);

      displayProgram.endUse();
    }


    if (previousGridIndex != currentGridIndex) {
      Log::info("Changed previous index " + std::to_string(currentGridIndex));
      previousGridIndex = currentGridIndex;
    }

    // Display GUI
    displayGUI();

    // Swap buffers
    glfwSwapBuffers(window.getGLFWwindow());
  }

  shutdownImGui();

  // Exit
  Log::message("Exiting program...");
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
