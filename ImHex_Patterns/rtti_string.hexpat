struct rtti_string_standalone{
  u8 struct_length;
  u8 string_length;
  if(struct_length != (string_length + 1))
  {
    std::print("FUCK");
  }
  char string[string_length];
  };

struct rtti_string_chunk_u8
{
  u8 chunk_size;
  rtti_string_standalone strings[chunk_size];
};
