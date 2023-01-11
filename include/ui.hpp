#pragma once

class UIPage{
  public:
  virtual void Setup() = 0;
  virtual void Render() = 0;
  virtual void Destroy() = 0;
  virtual void FileDropCallback(const char* path) = 0;
};

class TexToolsPage : public UIPage{
  public:
  void Setup() override;
  void Render() override;
  void Destroy() override;
  void FileDropCallback(const char* path) override;
};

namespace UI{
  namespace Pages{
    extern TexToolsPage TextureTools;
  }
}