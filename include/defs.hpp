#pragma once

#ifdef __APPLE__
#define IOS_SEEK_CUR std::ios_base::seekdir::cur
#else 
#define IOS_SEEK_CUR std::ios_base::seekdir::_S_cur
#endif