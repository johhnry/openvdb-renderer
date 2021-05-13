#ifndef OPENVDB_RENDERER_SRC_APP_APPLICATIONWINDOW_HPP_
#define OPENVDB_RENDERER_SRC_APP_APPLICATIONWINDOW_HPP_

#include <string>

#include <GLFW/glfw3.h>

class ApplicationWindow
{
public:
  ApplicationWindow();

  ApplicationWindow(const ApplicationWindow &other) = delete;
  ApplicationWindow(ApplicationWindow &&other) = delete;
  ApplicationWindow &operator=(const ApplicationWindow &other) = delete;
  ApplicationWindow &operator=(ApplicationWindow &&other) = delete;

  virtual ~ApplicationWindow();

public:
  void initialize(std::string title, const uint32_t width, const uint32_t height);

  // Getters
  GLFWwindow *getGLFWwindow() const;
  uint32_t getWidth() const;
  uint32_t getHeight() const;

  void update();

  // Static
  static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  static void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void mouseButtonCallBack(GLFWwindow *window, int button, int action,
                                  int mods);
  static float pmouseX, pmouseY, mouseX, mouseY;
  static bool mouseDragged;

private:
  GLFWwindow *window;
  std::string title;
  uint32_t width, height;
};

#endif /* OPENVDB_RENDERER_SRC_APP_APPLICATIONWINDOW_HPP_ */
