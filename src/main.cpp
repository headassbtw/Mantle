#include <core/core_file.hpp>
#include <rendering/render.hpp>

int main(int argc, char *argv[]) {
  Logger::Init();
  if(argc >= 2){
    core_kz2_file* core = disk_core_read(argv[1]);
    return 1;
  }

  return UI::Run();
}