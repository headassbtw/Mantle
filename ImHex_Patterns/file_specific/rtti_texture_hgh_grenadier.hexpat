#pragma endian big

//this is just me trying to map out a single file, pay no mind to it

#include </home/headass/cppProjects/Mantle/ImHex_Patterns/rtti_string.hexpat>
#include </home/headass/cppProjects/Mantle/ImHex_Patterns/rtti_texture.hexpat>
#include </home/headass/cppProjects/Mantle/ImHex_Patterns/rttibin.hexpat>

//                              first six bytes of unk2 | texture type
//------------------------------------------------------|---------------------------
rtti_texture_2 texture0 @ 0x10AD31; //AB 00 81 01 33 00 | detail map, combo of greyscale
rtti_texture_1 texture1 @ 0x1358E8; //81 00 80 01 80 00 | normal map in little endian?
rtti_texture_funky texture1point5 @ 0x1604B8; //dude what the fuck is this?
rtti_texture_1 texture2 @ 0x160764; //02 00 81 00 80 81 | probably color
rtti_texture_0 texture3 @ 0x18B322; //81 00 80 00 00 81 | normal map
rtti_texture_1 texture4 @ 0x235EDC; //81 00 80 01 80 00 | likely a detail map
rtti_texture_1 texture5 @ 0x240A9A; //81 00 80 01 80 00 | unknown
rtti_texture_1 texture6 @ 0x24B658; //B8 81 00 80 00 80 | probably a detail of sorts
rtti_texture_0 texture7 @ 0x2F6216; //00 80 01 00 81 01 | normal map
rtti_texture_1 texture8 @ 0x3A0DD0; //81 00 80 01 80 00 | same look as 6


struct rtti_stringchunk_v2{
  u16 string_count;
  rtti_string_standalone strings[string_count];
};
rtti_stringchunk_v2 string_chunk @ 0x36E6;

