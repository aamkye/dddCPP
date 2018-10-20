#pragma once

#include <structure/General.hpp>
#include <iostream>
#include <vector>
#include <bitset>

namespace ddd {
  class ConvertTool {
  public:
    auto bcdToDec(uint32_t _val) -> uint32_t;
    auto decToBcd(uint32_t _val) -> uint32_t;
    auto stringToHex(std::string input) -> std::string;
    auto hexToString(std::string input) -> std::string;
    auto trim(std::string str) -> std::string;
    auto bitShift(bVec arr) -> uint32_t;
    auto decToBin(uint32_t input) -> std::string;
    auto binToDec(std::string input) -> uint32_t;
    auto utf8(std::string str) -> std::string;
  };
}
