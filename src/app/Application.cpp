#include <cstdlib>
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


Application::Application() : window()
{
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

  vdbFileDialog.Display();

  // File dialog selection
  if (vdbFileDialog.HasSelected()) {
    std::string filename = vdbFileDialog.GetSelected().string();
    Log::info("Selected filename : " + filename);

    // Open VDB file
    vdbFile = std::make_unique<VDBFile>(filename);

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

  // Create VAO
  FullScreenVAO fullScreenVAO;
  Program displayProgram;

  try {
    // Vertex shader and fragment shader
    VertexShader vertexShader("../src/glsl/vertex.glsl");
    FragmentShader fragmentShader("../src/glsl/fragment.glsl");

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Display shader
    displayProgram.beginUse();
    fullScreenVAO.bind();

    fullScreenVAO.draw();

    fullScreenVAO.unbind();
    displayProgram.endUse();

    // Display GUI
    displayGUI();

    if (previousGridIndex != currentGridIndex) {
      Log::info("Changed previous index " + std::to_string(currentGridIndex));
      previousGridIndex = currentGridIndex;
    }

    // Swap buffers
    glfwSwapBuffers(window.getGLFWwindow());
  }

  shutdownImGui();

  // Exit
  Log::message("Exiting program...");
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
