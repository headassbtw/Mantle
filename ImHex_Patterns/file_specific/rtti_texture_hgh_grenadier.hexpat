#pragma endian big

//this is just me trying to map out a single file, pay no mind to it

#include </home/headass/cppProjects/Mantle/ImHex_Patterns/rtti_texture.hexpat>


//                                   first eight bytes of unk2 | texture type
//-------------------------------------------------------------|---------------------------
rtti_texture_2 texture0 @ 0x10AD31;
rtti_texture_1 texture1 @ 0x1358E8;
rtti_texture_3 texture2 @ 0x1604A6; //0x02AD76 long data

rtti_texture_1 texture00 @ 0x240A9A; //81 00 80 01 80 00 13 57 | unknown
rtti_texture_1 texture01 @ 0x24B658; //B8 81 00 80 00 80 00 0A | probably a detail of sorts
rtti_texture_0 texture02 @ 0x2F6216; //00 80 01 00 81 01 3B 00 | normal map
rtti_texture_1 texture03 @ 0x3A0DD0; //81 00 80 01 80 00 14 02 | same look as 1





