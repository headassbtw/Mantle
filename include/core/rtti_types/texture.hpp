#pragma once
#include <cstdint>

struct rtti_texture_base{
  uint32_t res0;
  uint32_t res1;
  uint32_t mipmaps;
  uint32_t texture_data_size;
  char* data;
};


struct rtti_texture_0 : rtti_texture_base
{
  char unk1[3]; //0x000180
  uint32_t texture_data_size;
  char unk2[9];
  char zero[6];
  uint32_t res0;
  uint32_t res1;
  char unk3[76];
  char begin[80];
  char* data;
  char end[72];
};

extern bool disk_read_rtti_texture(rtti_texture_base &rtti_texture, const char *filepath);