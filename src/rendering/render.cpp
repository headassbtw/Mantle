#include <GL/glew.h>
#include <GL/gl.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "resource.hpp"
#include <cstring>
#include <glm/common.hpp>
#include <cstdio>
#include <vector>
#include <rendering/render.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <mutex>
#include <chrono>
#include <thread>
#include <logger.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
using namespace std;

GLFWwindow* UI::gl_window;

int UI::window_height = 500;
int UI::window_width = 500;

void viewport_size_callback(GLFWwindow* window, int xpos, int ypos){
    UI::window_height = ypos;  
    UI::window_width = xpos;
    glViewport(0,0,xpos,ypos);
}

int UI::Run(){
  glewExperimental = true;
  if(!glfwInit()) fprintf(stderr, "Could not initialize GLFW\n");
  
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  UI::gl_window = glfwCreateWindow(UI::window_width, UI::window_height, "CORE tool", NULL, NULL);
  if(UI::gl_window == NULL){
    fprintf(stderr, "Failed to open window\n");
    glfwTerminate();
    return -1;
  }

  GLFWimage images[1];
  auto app_icon = stbi_load_from_memory(Resources::Icon, Resources::Icon_size, &images[0].width, &images[0].height, 0, 4);
  images[0].pixels = app_icon;
  glfwSetWindowIcon(UI::gl_window, 1, images);
  stbi_image_free(app_icon);

  glfwMakeContextCurrent(UI::gl_window);
  glfwSetFramebufferSizeCallback(UI::gl_window, viewport_size_callback);
  glfwShowWindow(UI::gl_window);
  glewExperimental = true;
  if(glewInit() != GLEW_OK){
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
  }

  glfwSetWindowSizeLimits(UI::gl_window, 800, 500, GLFW_DONT_CARE, GLFW_DONT_CARE);
  
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  ImGui::GetIO().IniFilename = NULL;
  ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Resources::SegoeUI_compressed, Resources::SegoeUI_compressed_size, 16);
  ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Resources::Impact_compressed, Resources::Impact_compressed_size, 16);
  ImGui::GetIO().Fonts->Build();
  auto style = ImGui::GetStyle();
  //style.Colors[ImGuiCol_WindowBg].w = 0.0;
  ImGui::GetStyle().ScrollbarRounding = 0.0f;
  ImGui::GetStyle().WindowBorderSize = 0.0f;
  ImGui::GetStyle().FrameBorderSize = 0.0f;
  ImGui::GetStyle().PopupBorderSize = 0.0f;
  ImGui::GetStyle().TabRounding = 0.0f;
  ImGui::GetStyle().WindowPadding = {8.0f,8.0f};
  ImGui::GetStyle().Colors[ImGuiCol_TextDisabled] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_Border] = ImVec4(0.55f, 0.55f, 0.55f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_Separator] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f);
  ImGui::GetStyle().Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.7f, 0.7f, 0.7f, 0.4f);
  ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.08f);
  ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.3f);
  ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.54f);
  ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_Header] = ImVec4(1.0f, 1.0f, 1.0f, 0.08f);
  ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.24f);
  ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.47f);
  ImGui::GetStyle().Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
  ImGui::GetStyle().Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.35f);
  ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.63f, 0.63f, 0.63f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.93f, 0.93f, 0.93f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_Tab] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_TabHovered] = ImVec4(0.71f, 0.71f, 0.71f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_TabActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.0f);

  ImGui::GetStyle().Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0f, 1.0f, 1.0f, 0.2f);
  ImGui::GetStyle().Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.67f);
  ImGui::GetStyle().Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_SeparatorActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

  ImGui_ImplGlfw_InitForOpenGL(UI::gl_window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  glfwSetInputMode(UI::gl_window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwPollEvents();
  glViewport(0,0,UI::window_width,UI::window_height);
  glClearColor(0.1, 0.1, 0.1, 255);
  
  UI::SetupInterface();
  do{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

    // actual interface
    UI::RenderInterface();
    // end interface

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
    }
    glfwSwapBuffers(UI::gl_window);
  }
  while(glfwWindowShouldClose(UI::gl_window) == 0);
  UI::DestroyInterface();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();


  return 0;
}
