#ifndef CORETOOL_CORE_FILE_HPP
#define CORETOOL_CORE_FILE_HPP

#pragma once
#include <vector>
#include <string>
struct core_kz2_file{
  char version[4];
  char unk1[19];
  uint8_t included_filetypes_count;
  std::vector<std::string> included_filetypes;
};

core_kz2_file* disk_core_read(std::string file_path);

#endif //CORETOOL_CORE_FILE_HPP
