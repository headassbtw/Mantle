#pragma once
#include <cstdint>

struct rtti_Texture{
  char begin[72]; //full of 0xEE
  //char unk0[18 - 23]; //LENGTH VARIES OF BULLSHIT!
  char unk1[4]; //likely blank

  uint32_t res0; // not sure which these are (height or width)
  uint32_t res1;

  char unk2[8]; //idk

  uint32_t mipmap_count; //JUST SPECULATION, is 11 when res is 1024 (proper mipmap count for that res)


  char end[50]; //full of 0x50
};