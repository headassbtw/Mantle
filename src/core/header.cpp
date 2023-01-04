#include <core/core_file.hpp>
#include <cstring>

core_kz2_file::core_kz2_file(){
  memset(version,0x00,8);
  memset(unk1,0x00,19);
}
core_kz2_file::~core_kz2_file(){
  for(char* filetype : included_filetypes){
    free(filetype); //look mom i'm using C++ properly!
  }
}