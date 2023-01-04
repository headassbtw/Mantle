

struct rtti_string{
  u8 str_len;
  char string[str_len];
  };

struct rtti_bin_file_header{
  char file_identifier[15]; //RTTIBin<1.58> and the two 0x20 that follows
  char unk1[17];
  u8 strchunk_length;
  rtti_string strchunk[strchunk_length];
};

struct RTTIBin{
  rtti_bin_file_header file_header;
};

RTTIBin rtti @ 0x00;

