#include "core/rtti_types/string.hpp"
#include "logger.hpp"
#include <core/core_file.hpp>
#include <cstring>
#include <exception>
#include <istream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

bool disk_core_read(core_kz2_file* &core_file, std::string file_path){
  std::ifstream in_stream(file_path.c_str());

  if(!in_stream.good()){
    Logger::Critical("disk_core_read: input file was bad\n");
    abort();
  }
  char rtti_bin[8]           = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //just verification
  char rtti_bin_extpected[8] = {0x52,0x54,0x54,0x49,0x42,0x69,0x6E,0x00}; 

  in_stream.read(rtti_bin, 7);

  if(strcmp(rtti_bin, rtti_bin_extpected) != 0){
    Logger::Critical("disk_core_read: input file was not a proper core archive\n");
    Logger::Critical("\"%s\" vs \"%s\"\n",rtti_bin,rtti_bin_extpected);
    abort();
  }
  else{
    Logger::Info("disk_core_read: input file magic was \"%s\"\n",rtti_bin);
  }

  char core_version[9]           = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // trailing 0x00 because C++ is stupid and can't just compare values of the array without a null-termination
  char core_version_extpected[9] = {0x3C,0x31,0x2E,0x35,0x38,0x3E,0x20,0x20,0x00}; // "<1.58>  "

  in_stream.read(core_version, 8);
  if(strcmp(core_version,core_version_extpected) != 0){
    Logger::Critical("disk_core_read: core archive version not supported\n");
    Logger::Critical("\"%s\" vs \"%s\"\n",core_version,core_version_extpected);
    abort();
  }
  else{
    Logger::Info("disk_core_read: core archive was of proper version 1.58\n");
  }
  memcpy(core_file->version,core_version,8);
  #pragma region TODO
  /////////////////////////////////////////////////////////////////////////////////////
  //COME BACK TO ME YOU BITCH
  in_stream.seekg(17,std::ios_base::seekdir::_S_cur); //skips over shit i don't know yet
  //SERIOUSLY IT'S GONNA BITE YOU IN THE ASS
  /////////////////////////////////////////////////////////////////////////////////////
  #pragma endregion

  in_stream.read((char*)&core_file->included_filetypes_count,1);

  printf("%i included filetypes\n",core_file->included_filetypes_count);
  
  for(int i = 0; i < core_file->included_filetypes_count; i++){
    uint8_t str_length;
    in_stream.read((char*)&str_length, 1); //the lenth of the filetype
    char filetype[str_length+1]; //null-terminated because C++ expects them to be like that to be properly printed
    memset(filetype,0x00,str_length+1);
    in_stream.read(filetype, str_length);
    core_file->included_filetypes.push_back(filetype);
    if(i == core_file->included_filetypes_count-1) printf("`--");
    else                                           printf("|--");
    printf("%s | %zu\n",filetype,strlen(filetype));
    //this is just a sanity check to see the data in the vector isn't immediately being corrupted
    if(i == core_file->included_filetypes_count-1) printf("  `-");
    else                                           printf("| `-");
    printf("%s | %zu\n",core_file->included_filetypes[i],strlen(core_file->included_filetypes[i]));
  }
  if(core_file->included_filetypes_count != core_file->included_filetypes.size()){
    throw new std::runtime_error("file amount mismatch in core_file->included_filetypes_count!");
  }

  // weird thing, string chunks in the asset type in the middle of 
  // LocalCachePS3/lumps/characters.hgh_grenadier.core
  // instead of starting with one byte containing the length, there are two, the last is correct but the first is *always* 1 higher


  return true;
}