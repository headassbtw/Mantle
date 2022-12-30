#include "logger.hpp"
#include <core/core_file.hpp>
#include <cstring>
#include <istream>
#include <stdio.h>
#include <iostream>
#include <fstream>

core_kz2_file* disk_core_read(std::string file_path){
  core_kz2_file* core_file = new core_kz2_file();
  std::ifstream in_stream(file_path.c_str());

  if(!in_stream.good()){
    Logger::Critical("disk_core_read: input file was bad\n");
    abort();
  }
  char rtti_bin[7]; //just verification

  in_stream.read(rtti_bin, 7);

  if(strcmp(rtti_bin, "RTTIBin") != 0){
    Logger::Critical("disk_core_read: input file was not a proper core archive\n");
    abort();
  }
  in_stream.seekg(1,std::ios_base::seekdir::_S_cur); //skips the "<"

  char core_version[4] = {'d','i','c','k'};

  in_stream.read(core_file->version, 4);
  printf("Core file is version %s\n", core_file->version);
  if(strcmp(core_file->version,"1.58") != 0){
    Logger::Critical("disk_core_read: core archive version not supported\n");
    abort();
  }

  /////////////////////////////////////////////////////////////////////////////////////
  //COME BACK TO ME YOU BITCH
  in_stream.seekg(20,std::ios_base::seekdir::_S_cur); //skips over shit i don't know yet
  //SERIOUSLY IT'S GONNA BITE YOU IN THE ASS
  /////////////////////////////////////////////////////////////////////////////////////

  in_stream.read((char*)&core_file->included_filetypes_count,1);

  printf("%i included filetypes\n",core_file->included_filetypes_count);
  
  for(int i = 0; i < core_file->included_filetypes_count; i++){
    uint8_t str_length;
    in_stream.read((char*)&str_length, 1); //the lenth of the filetype
    char filetype[str_length];
    in_stream.read(filetype, str_length);
    //core_file->included_filetypes.push_back(std::string(filetype));
    if(i == core_file->included_filetypes_count-1) printf("`--");
                                             else  printf("|--");
    printf("%s\n",filetype);
  }

  // calling it for tonight
  // weird thing, string chunks in the asset type in the middle of 
  // /kronos/Games/PS3/Killzone 2/PS3_GAME/USRDIR/LocalCachePS3/lumps/characters.hgh_grenadier.core
  // instead of starting with one byte containing the length, there are two, the last is correct but the first is *always* 1 higher


  return core_file;
}