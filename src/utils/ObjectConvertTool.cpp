#include <utils/ObjectConvertTool.hpp>
#include <structure/General.hpp>
#include <iostream>
#include <vector>

auto ddd::ObjectConvertTool::genericParse(const ddd::structure::general::iObj& obj, size_t beg, size_t end) -> uint32_t {
  return bitShift(bVec(obj.raw.begin() + beg, obj.raw.end() + end));
}

auto ddd::ObjectConvertTool::genericParse(const ddd::structure::general::hObj& obj, size_t beg, size_t end) -> std::string {
  return utf8(stringToHex(std::string(obj.raw.begin() + beg, obj.raw.end() + end)));
}

auto ddd::ObjectConvertTool::genericParse(const ddd::structure::general::sObj& obj, size_t beg, size_t end) -> std::string {
  return utf8(trim(std::string(obj.raw.begin() + beg, obj.raw.end() + end)));
}

auto ddd::ObjectConvertTool::parse(ddd::structure::general::iObj& obj, size_t beg, size_t end) -> void {
  obj.data = genericParse(obj, beg, end);
}

auto ddd::ObjectConvertTool::parse(ddd::structure::general::hObj& obj, size_t beg, size_t end) -> void {
  obj.data = genericParse(obj, beg, end);
}

auto ddd::ObjectConvertTool::parse(ddd::structure::general::sObj& obj, size_t beg, size_t end) -> void {
  obj.data = genericParse(obj, beg, end);
}

auto ddd::ObjectConvertTool::parse(ddd::structure::general::rObj&, size_t, size_t) -> void {}

auto ddd::ObjectConvertTool::parseBCD(const ddd::structure::general::rObj& obj, size_t beg, size_t end) -> uint32_t {
  return bcdToDec(bitShift(bVec(obj.raw.begin() + beg, obj.raw.begin() + end)));
}
