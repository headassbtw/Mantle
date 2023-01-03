#include <core/core_file.hpp>
#include <cstring>

core_kz2_file::core_kz2_file(){
  memset(version,0x00,8);
  memset(unk1,0x00,19);
}