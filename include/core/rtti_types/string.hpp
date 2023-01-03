#pragma once
#include <cstdint>

//i should NOT need to do this.
struct rtti_string{
  uint8_t string_length;
  char* string;
};