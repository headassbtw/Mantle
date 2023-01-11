#include <core/rtti_types/texture.hpp>
#include <iostream>
#include <cstring>
#include <logger.hpp>
#include <fstream>
#include <stdexcept>

bool disk_read_rtti_texture(rtti_texture_base &rtti_texture, const char *filepath){;
  std::ifstream in_stream(filepath);
   if(!in_stream.good()){
    Logger::Critical("read_rtti_texture_0: input file was bad\n");
    abort();
  }
  char unk1[4] = {0x01,0x01,0x01};
  char tex_0[4] = {0x00,0x01,(char)0x80};
  in_stream.read(unk1,3);
  if(memcmp(unk1, tex_0,3) == 0){ //is type 0
  Logger::Debug("C++ thinks \"%s\" is the same as \"%s\", is it right? \n",unk1,tex_0);
    in_stream.read((char*)rtti_texture.texture_data_size,4);
    rtti_texture.data = (char*)malloc(rtti_texture.texture_data_size);
    in_stream.seekg(15,std::ios_base::seekdir::cur); // unknown
    in_stream.read((char*)rtti_texture.res0,4);
    in_stream.read((char*)rtti_texture.res1,4);
    in_stream.seekg(76,std::ios_base::seekdir::cur); // unknown
    //before we start with the texture data we can verify the size
    if (in_stream.tellg() != 106){
      Logger::Critical("File progress mismatch,. terminating. \n");
      throw(new std::runtime_error("File progress mismatch."));
    }
    in_stream.seekg(80,std::ios_base::seekdir::cur); // begin
    in_stream.read(rtti_texture.data,rtti_texture.texture_data_size);
    in_stream.seekg(72,std::ios_base::seekdir::cur); // end
    in_stream.close();
    return true;
  }
  else{
    in_stream.close();
    return false;
  }




}