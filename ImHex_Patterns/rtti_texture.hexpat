#pragma endian big

//just find one, it should error on the array size if it's the wrong one

struct rtti_texture_0
{
  char unk1[3]; //0x000180
  u32 size;
  char unk2[9];
  u48 zero;
  u32 res1;
  u32 res2;
  char unk3[76];
  char begin[80];
  char data[size];
  char end[72];
};
struct rtti_texture_1
{
  char unk1[3]; //0x000180
  u32 size;
  char unk2[13];
  u48 zero;
  u32 res1;
  u32 res2;
  char unk3[76];
  char begin[80];
  char data[size];
  char end[72];
};
struct rtti_texture_2
{
  char unk1[3]; //0x810080
  u32 size;
  char unk2[6];
  u48 zero;
  u32 res1;
  u32 res2;
  char unk3[48];
  u32 size_maybe;
  char unk4[24];
  char begin[80];
  char data[size_maybe];
  char end[72];
};
struct rtti_texture_3 //WIP
{
  char unk1[3]; //0x000181
  char unk2[63];
  u32 res1;
  char unk3[12];
  u32 res2;
  char unk4[24];
  char begin[80];
};


