#include "GLFW/glfw3.h"
#include "imgui_internal.h"
#include "resource.hpp"
#include <imgui.h>
#include <rendering/render.hpp>
#include <rendering/gl_tools.hpp>
#include <stb_image.h>
#include <core/core_file.hpp>
#include <optional>
#include <logger.hpp>
#include <tinyfiledialogs.h>

bool show_imgui_demo_window = false;
ImU32 imgui_menubar_background_color;
ImU32 imgui_tab_active_color;

int interface_selected_window = 0;
GLuint program_icon;

std::string file_name_temp;
core_kz2_file* core_file;
bool has_core_file = false;

void file_open(const char* path){
  file_name_temp = std::string(path);
  has_core_file = disk_core_read(core_file, std::string(path));
}

void file_drop_callback(GLFWwindow* window, int count, const char** paths)
{
  file_open(paths[0]);
}

void TextCentered(const char* text){
  
}

void UI::SetupInterface(){
  imgui_menubar_background_color = ImGui::GetColorU32(ImGuiCol_MenuBarBg);
  imgui_tab_active_color = ImGui::GetColorU32(ImGuiCol_TabActive);

  program_icon = GetGLTexture(Resources::Icon, Resources::Icon_size);
  glfwSetDropCallback(UI::gl_window, file_drop_callback);
  core_file = new core_kz2_file();

}

void UI::DestroyInterface(){
  glDeleteTextures(1,&program_icon);
  delete core_file;
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

void RenderNoFileDialog(){
  const char* message = "Drop a file on here to start.\n or click Here to browse";
  auto window_size = ImGui::GetWindowSize();
  auto text_size   = ImGui::CalcTextSize(message);
  const ImVec2 here_prompt_width = ImGui::CalcTextSize("Here");

  ImGui::SetCursorPosX((window_size.x - text_size.x) * 0.5f);
  ImGui::SetCursorPosY((window_size.y - text_size.y) * 0.5f);
  static bool a;
  ImGui::Text("Drop a file on here to start.");
  ImGui::SetCursorPosX((window_size.x - text_size.x) * 0.5f);
  ImGui::Text("or click ");
  ImGui::SameLine();
  if(ImGui::Selectable("Here",a,ImGuiSelectableFlags_SelectOnClick,here_prompt_width)){
    const char* exts[1];
    exts[0] = "*.core";
    char const * selection = tinyfd_openFileDialog( // there is also a wchar_t version
        "Select file", // title
        NULL, // optional initial directory
        1, // number of filter patterns
        exts,
        NULL, // optional filter description
        0 // forbid multiple selections
    );
    if(selection != NULL){
      file_open(selection);
    }
    
  }
  ImGui::SameLine();
  ImGui::Text(" to browse");

}

void RenderMainPage(){
  if(!has_core_file) RenderNoFileDialog();
  else if(has_core_file){
    ImGui::Text("Version: %s", core_file->version);
    ImGui::Text("Filename: %s",file_name_temp.c_str());
    if (ImGui::TreeNode((void*)(intptr_t)0, "File types (%hhu)", core_file->included_filetypes_count))
    {
      for(auto file : core_file->included_filetypes){
        ImGui::Text("%s",file);
      }
      ImGui::TreePop();
    }
  }
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