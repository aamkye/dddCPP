/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */
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
