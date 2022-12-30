#include "core/core_file.hpp"
#include <logger.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <rendering/render.hpp>
using namespace std;





int main(int argc, char *argv[]) {
  Logger::Init();
  if(argc >= 2){
    core_kz2_file* core = disk_core_read(argv[1]);
    return 1;
  }

  return UI::Run();
}