#pragma once
#include <GLFW/glfw3.h>
namespace UI{
  extern GLFWwindow* gl_window;
  extern int window_width;
  extern int window_height;
  
  int Run();
  
  void SetupInterface();
  void RenderInterface();
  void DestroyInterface();
}