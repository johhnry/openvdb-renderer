#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "log/Log.hpp"

#include "ApplicationWindow.hpp"
#include <string>
#include <cstdlib>

float ApplicationWindow::pmouseX = 0;
float ApplicationWindow::pmouseY = 0;
float ApplicationWindow::mouseX = 0;
float ApplicationWindow::mouseY = 0;

bool ApplicationWindow::mouseDragged = false;

ApplicationWindow::ApplicationWindow() {}

ApplicationWindow::~ApplicationWindow()
{
  glfwDestroyWindow(window);
}

void ApplicationWindow::initialize(const std::string title, const uint32_t width, const uint32_t height)
{
  this->title = title;
  this->width = width;
  this->height = height;

  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

  if (!window) {
    Log::error("GLFW: error when creating a window");
  } else {
    Log::success("GLFW: Initialized window : " + this->title);
  }

  glfwMakeContextCurrent(window);

  // Set glfw window callbacks
  glfwSetFramebufferSizeCallback(window, ApplicationWindow::framebufferSizeCallback);
  glfwSetKeyCallback(window, ApplicationWindow::keyCallBack);

  glfwSetMouseButtonCallback(window, ApplicationWindow::mouseButtonCallBack);
}

GLFWwindow *ApplicationWindow::getGLFWwindow() const
{
  return window;
}

uint32_t ApplicationWindow::getWidth() const
{
  return width;
}

uint32_t ApplicationWindow::getHeight() const
{
  return height;
}

void ApplicationWindow::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  (void)window;
  glViewport(0, 0, width, height);
}

void ApplicationWindow::keyCallBack(GLFWwindow *window, int key, int scancode,
                                    int action, int mods)
{
  (void)mods;
  (void)scancode;

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    Log::message("Close window");
  }
}

void ApplicationWindow::update()
{
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  ApplicationWindow::pmouseX = mouseX;
  ApplicationWindow::pmouseY = mouseY;
  ApplicationWindow::mouseX = xpos;
  ApplicationWindow::mouseY = ypos;
}

void ApplicationWindow::mouseButtonCallBack(GLFWwindow *window, int button, int action,
                                int mods)
{
  (void)window;
  (void)mods;

  if (button == GLFW_MOUSE_BUTTON_LEFT)
  {
    if (action == GLFW_PRESS)
    {
      mouseDragged = true;
    } else if (action == GLFW_RELEASE)
    {
      mouseDragged = false;
    }
  }
}
