module;
#include <spdlog/spdlog.h>

#include <iostream>
export module Hello;
export void hello() {
  std::cout << "Hello World!\n";
  spdlog::info("Hello World!");
}
