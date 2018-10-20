#pragma once

#include <fstream>
#include <streambuf>
#include <iostream>
#include <string>

namespace ddd {
  class Limiter {
  public:
    Limiter();
  private:
    std::string getMac(const std::string &ifname);
    uint32_t getTime();
    bool check();
  };
}
