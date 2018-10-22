#include <utils/ConvertTool.hpp>
#include <structure/General.hpp>
#include <iostream>
#include <vector>
#include <bitset>
#include <utf8.h>

/**
 * ([0] << 16) +
 * ([1] << 8) +
 * ([2] << 0)
 */
auto ddd::ConvertTool::bitShift(bVec arr) -> uint32_t {
  uint32_t value = 0;
  uint32_t b     = arr.size() - 1;

  for(uint32_t a = 0; a < arr.size();) {
    value += ((uint32_t)(arr[a++]) << b-- * 8);
  }
  return value;
}

auto ddd::ConvertTool::bcdToDec(uint32_t val) -> uint32_t {
  return ((val / 16 * 10) + (val % 16));
}

auto ddd::ConvertTool::decToBcd(uint32_t val) -> uint32_t {
  return ((val / 10 * 16) + (val % 10));
}

auto ddd::ConvertTool::stringToHex(std::string input) -> std::string {
  std::string              output;
  static const char* const lut = "0123456789ABCDEF";
  size_t                   len = input.length();
  output.reserve(2 * len);
  for(size_t i = 0; i < len; ++i) {
    const unsigned char c = input[i];
    output.push_back(lut[c >> 4]);
    output.push_back(lut[c & 15]);
  }
  return output;
}

auto ddd::ConvertTool::hexToString(std::string input) -> std::string {
  std::string              output;
  static const char* const lut = "0123456789ABCDEF";
  size_t                   len = input.length();
  if(len & 1) return "";
  output.reserve(len / 2);
  for(size_t i = 0; i < len; i += 2) {
    char        a = input[i];
    const char* p = std::lower_bound(lut, lut + 16, a);
    if(*p != a) return "";
    char        b = input[i + 1];
    const char* q = std::lower_bound(lut, lut + 16, b);
    if(*q != b) return "";
    output.push_back(((p - lut) << 4) | (q - lut));
  }
  return output;
}

auto ddd::ConvertTool::decToBin(uint32_t input) -> std::string {
  return std::bitset<16>(input).to_string();
}

auto ddd::ConvertTool::binToDec(std::string input) -> uint32_t {
  return std::bitset<16>(input).to_ulong();
}

auto ddd::ConvertTool::trim(std::string str) -> std::string {
  str.erase(0, str.find_first_not_of(' ')); // prefixing spaces
  str.erase(str.find_last_not_of(' ') + 1); // surfixing spaces
  return str;
}

auto ddd::ConvertTool::utf8(std::string str) -> std::string {
    return str;
}
