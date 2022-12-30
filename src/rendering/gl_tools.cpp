#include "logger.hpp"
#include <rendering/gl_tools.hpp>
#include <stb_image.h>
GLuint GetGLTexture(const unsigned char *file_data, int size){
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int x, y;
  auto data = stbi_load_from_memory(file_data, size, &x, &y, 0, 4);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
  return texture;
}