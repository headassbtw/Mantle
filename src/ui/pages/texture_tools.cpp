#include <ui.hpp>
#include "imgui_internal.h"
#include <imgui.h>
#include <string>
#include <tinyfiledialogs.h>
#include <core/rtti_types/texture.hpp>
#include <core/core_texture_extractor_beta.hpp>

TexToolsPage UI::Pages::TextureTools;
bool has_file; //a file has been dropped. it exists. nothing more.
std::string tex_temp;
GLuint tex;

void texture_open(const char* path){
  tex_temp = std::string(path);
  has_file = true;
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
  if(has_file){
    ImGui::Text("Filename: %s",tex_temp.c_str());

    ImGui::Text("Enter offset of texture:");
    static int offset = 1443684;
    ImGui::InputInt("##offset", &offset, 0, 0, ImGuiInputTextFlags_CharsHexadecimal);
    //160764
    if(ImGui::Button("Convert")){
      tex = RTTI::find_tex(offset, tex_temp.c_str());
    }

  }
  else{
    RenderNoTextureDialog();
  }
}

void TexToolsPage::Destroy(){

}