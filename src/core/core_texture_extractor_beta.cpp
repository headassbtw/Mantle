#include <core/core_texture_extractor_beta.hpp>
#include <cstring>
#include <defs.hpp>
#include <fstream>
#include <rendering/gl_tools.hpp>
#include <stb_image.h>
#include <iostream>
#include <logger.hpp>

GLuint RTTI::find_tex(uint32_t offset, const char *filepath){
  auto file = std::ifstream(filepath, std::ios::binary);

  file.seekg(offset);
  char tex_type[3];
  char tex_type_00[3] = {(char)0x00, (char)0x01, (char)0x80};
  char tex_type_01[3] = {(char)0x00, (char)0x01, (char)0x80};
  //there are a few we can fuck with here, gonna focus on some shit like uhhhh 0x000180 thanks
  file.read(tex_type, 3);
  uint32_t size;
  uint32_t res0;
  uint32_t res1;

  char* voidd = (char*)malloc(80); //cba to read from current offset

  if(memcmp(tex_type, tex_type_01, 3) == 0){
    file.read((char*)&size,4);
    file.read(voidd,19);
    file.read((char*)&res0,4);
    file.read((char*)&res1,4);
  }
    #ifdef __MANTLE_LITTLE_ENDIAN__
      res0 = __builtin_bswap32(res0);
      res1 = __builtin_bswap32(res1); //the PS3 is big endian, your machine is not!
      size = __builtin_bswap32(size);
    #endif
    Logger::Info("res0: %d | res1: %d | size: %d\n", res0,res1,size);

    file.read(voidd,76);
    file.read(voidd,80);
    
    char* full_image_data = (char*)malloc(size+128);

    char start_dds_header[128] = {
    (char)0x44, (char)0x44, (char)0x53, (char)0x20, (char)0x7C, (char)0x00, (char)0x00, (char)0x00,
    (char)0x07, (char)0x10, (char)0x0A, (char)0x00, (char)0x00, (char)0x04, (char)0x00, (char)0x00,
    (char)0x00, (char)0x04, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x08, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x0B, (char)0x00, (char)0x00, (char)0x00,
    (char)0x47, (char)0x49, (char)0x4D, (char)0x50, (char)0x2D, (char)0x44, (char)0x44, (char)0x53,
    (char)0x5C, (char)0x09, (char)0x03, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x00, (char)0x00, (char)0x00,
    (char)0x04, (char)0x00, (char)0x00, (char)0x00, (char)0x44, (char)0x58, (char)0x54, (char)0x31,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x08, (char)0x10, (char)0x40, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00};

    memcpy(start_dds_header+12,(char*)&res0,4);
    memcpy(start_dds_header+16,(char*)&res1,4);
    memcpy(full_image_data,start_dds_header,128);
    memcpy(full_image_data+128,image_data,size);


    file.read((char*)full_image_data+128,size);

    auto out_file = std::ofstream("/home/headass/cppProjects/Mantle/out.dds", std::ios::binary);

    out_file.write(full_image_data, size+128);


    free(voidd);
    //free(image_data);
    free(full_image_data);
  return 0;
}