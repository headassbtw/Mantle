#pragma endian big

#include </home/headass/cppProjects/Mantle/ImHex_Patterns/rttibin.hexpat>

struct rtti_string_standalone{
  u8 struct_length;
  u8 string_length;
  if(struct_length != (string_length + 1))
  {
    std::print("FUCK");
  }
  char string[string_length];
};

struct rtti_stringchunk_v2{
  u8 string_count;
  rtti_string_standalone strings[string_count];
};


rtti_stringchunk_v2 rtti_stringchunk_v2_at_0x95F @ 0x960;
