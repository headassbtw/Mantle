#pragma once
#include <vector>
#include <string>
struct core_kz2_file{
  char version[8];
  char unk1[19];
  uint8_t included_filetypes_count;
  std::vector<char*> included_filetypes;

  core_kz2_file();
  ~core_kz2_file();
};


bool disk_core_read(core_kz2_file* &core_file, std::string file_path);
