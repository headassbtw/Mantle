#include "GLFW/glfw3.h"
#include "resource.hpp"
#include <imgui.h>
#include <rendering/render.hpp>
#include <rendering/gl_tools.hpp>
#include <stb_image.h>
bool show_imgui_demo_window = false;
ImU32 imgui_menubar_background_color;
ImU32 imgui_tab_active_color;

int interface_selected_window = 0;

GLuint program_icon;

void UI::SetupInterface(){
  imgui_menubar_background_color = ImGui::GetColorU32(ImGuiCol_MenuBarBg);
  imgui_tab_active_color = ImGui::GetColorU32(ImGuiCol_TabActive);

  program_icon = GetGLTexture(Resources::Icon, Resources::Icon_size);

}

void UI::DestroyInterface(){
  glDeleteTextures(1,&program_icon);
}

void RenderTopBar(){
  ImGui::SetNextWindowPos({0,0});
  ImGui::SetNextWindowSize({200,10});
  if(ImGui::Begin("##MenuBarBox",NULL,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)){
    if(ImGui::BeginMenuBar()){
      if(ImGui::BeginMenu("File")){
        if(ImGui::MenuItem("Quit","ALT + F4")){
          glfwSetWindowShouldClose(UI::gl_window,true);
        }
        
        ImGui::EndMenu();
      }// File

      if(ImGui::BeginMenu("Debug")){
        ImGui::MenuItem("Show ImGui demo window",NULL,&show_imgui_demo_window);
        
        ImGui::EndMenu();
      }// Debug

      ImGui::EndMenuBar();
    }

    auto bg_draw_list = ImGui::GetBackgroundDrawList();
    bg_draw_list->AddQuadFilled({200,22}, {(float)UI::window_width,22}, {(float)UI::window_width,0}, {200,0}, imgui_menubar_background_color);
    bg_draw_list->AddLine({0,21}, {(float)UI::window_width,21}, imgui_tab_active_color);

    ImGui::End();
  }// MenuBarBox

  ImGui::SetNextWindowPos({200,0});
  ImGui::SetNextWindowSize({(float)UI::window_width-320,10});
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,{8,0});
  if(ImGui::Begin("##MenuBarTabBox",NULL,ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)){
    if(ImGui::BeginTabBar("##MenuBarTabList")){
      interface_selected_window = -1;
      if(ImGui::BeginTabItem("Main")){
        interface_selected_window = 0;
        ImGui::EndTabItem();
      } //Main

      if(ImGui::BeginTabItem("About Tool")){
        interface_selected_window = 1;
        ImGui::EndTabItem();
      } //Secondary

      ImGui::EndTabBar();
    }// MenuBarTabList

    ImGui::End();
  }// MenuBarTabBox
  ImGui::PopStyleVar(1);

  ImGui::SetNextWindowPos({(float)UI::window_width-120,0});
  ImGui::SetNextWindowSize({120,10});
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,{8,0});
  if(ImGui::Begin("##MenuBarVersionBox",NULL,ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)){
    ImGui::Text("pre-alpha v%i.%i.%i",MANTLE_VERSION_MAJOR,MANTLE_VERSION_MINOR,MANTLE_VERSION_PATCH);

    ImGui::End();
  }// MenuBarVersionBox
  ImGui::PopStyleVar(1);
}

void RenderMainPage(){
  ImGui::Text("I'd probably put a file picker here or something");
}

void RenderAboutPage(){
  
  ImGui::Image((void*)(intptr_t)program_icon,{220,220});
  ImGui::SameLine();
  ImGui::BeginGroup();
  ImGui::SetWindowFontScale(2);
  ImGui::Text("Mantle");
  ImGui::SetWindowFontScale(1);
  ImGui::Text("A bullshit tool to deal with the bullshit .core archive format used in Killzone 2 (2009, PS3)");
  ImGui::Text("Made with pure unadulturated programmer rage by headassbtw");
  ImGui::EndGroup();
}

void UI::RenderInterface(){
  RenderTopBar();

  ImGui::SetNextWindowPos({0,22});
  ImGui::SetNextWindowSize({(float)UI::window_width,(float)UI::window_height-21});
  if(ImGui::Begin("MainInterfaceWindow",NULL,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse)){
    switch(interface_selected_window){
      case 0:
        RenderMainPage();
        break;
      case 1:
        RenderAboutPage();
        break;
      default:
        ImGui::Text("No Menu Selected");
        break;
    }
    ImGui::End();
  }


  

  if(show_imgui_demo_window) ImGui::ShowDemoWindow();
}