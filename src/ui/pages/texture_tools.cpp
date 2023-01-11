#include <ui.hpp>
#include "imgui_internal.h"
#include <imgui.h>
#include <string>
#include <tinyfiledialogs.h>
#include <core/rtti_types/texture.hpp>

TexToolsPage UI::Pages::TextureTools;
bool has_tex = false;
bool tex_valid = false;
rtti_texture_base texture;

std::string tex_temp;

void texture_open(const char* path){
  has_tex = true;
  tex_temp = std::string(path);
  tex_valid = disk_read_rtti_texture(texture, path);
}

void TexToolsPage::FileDropCallback(const char* path){
  texture_open(path);
}

void TexToolsPage::Setup(){

}

void RenderNoTextureDialog(){
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
    exts[0] = "*.bin";
    char const * selection = tinyfd_openFileDialog( // there is also a wchar_t version
        "Select file", // title
        NULL, // optional initial directory
        1, // number of filter patterns
        exts,
        NULL, // optional filter description
        0 // forbid multiple selections
    );
    if(selection != NULL){
      texture_open(selection);
    }
    
  }
  ImGui::SameLine();
  ImGui::Text(" to browse");

}

void TexToolsPage::Render(){
  if(has_tex)
    if(tex_valid){
      ImGui::Text("HEY, texture tools page goes here\n");
    }
    else{
      ImGui::Text("Sorry, that texture file was invalid,\nclick to try again:");
      if(ImGui::Button("Retry"))
      has_tex = false;
    }
  
  else{
    RenderNoTextureDialog();
  }
}

void TexToolsPage::Destroy(){

}