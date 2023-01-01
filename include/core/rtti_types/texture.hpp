#pragma once
#include <cstdint>

struct rtti_Texture{
  char begin[72]; //full of 0xEE
  char unk1[26]; //lmao kinda just lazy

  uint32_t res0; // not sure which these are (height or width)
  uint32_t res1;

  char end[50]; //full of 0x50
};