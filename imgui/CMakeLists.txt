cmake_minimum_required(VERSION 3.6)

add_library(
  imgui STATIC
  imconfig.h
  imgui.cpp
  imgui.h
  imgui_demo.cpp
  imgui_draw.cpp

  imgui_tables.cpp
  imgui_widgets.cpp

  imgui_impl_glfw.cpp
  imgui_impl_opengl3.cpp
  imgui_impl_glfw.h
  imgui_impl_opengl3.h

  imgui_internal.h
  stb_rect_pack.h
  stb_textedit.h
  stb_truetype.h

  imfilebrowser.h
)
