#pragma once
#include <gl.hpp>
#include <cstdint>

namespace RTTI{
  GLuint find_tex(uint32_t offset, const char* filepath);
}