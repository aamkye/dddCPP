#pragma once

#include <utils/ConvertTool.hpp>
#include <structure/General.hpp>
#include <iostream>
#include <vector>

namespace ddd {
  class ObjectConvertTool : public ConvertTool {
  public:
    auto parse(ddd::structure::general::iObj& obj, size_t beg = 0, size_t end = 0) -> void;
    auto parse(ddd::structure::general::hObj& obj, size_t beg = 0, size_t end = 0) -> void;
    auto parse(ddd::structure::general::sObj& obj, size_t beg = 0, size_t end = 0) -> void;
    auto parse(ddd::structure::general::rObj&, size_t = 0, size_t = 0) -> void;
    auto genericParse(const ddd::structure::general::iObj& obj, size_t beg = 0, size_t end = 0) -> uint32_t;
    auto genericParse(const ddd::structure::general::hObj& obj, size_t beg = 0, size_t end = 0) -> std::string;
    auto genericParse(const ddd::structure::general::sObj& obj, size_t beg = 0, size_t end = 0) -> std::string;
    auto parseBCD(const ddd::structure::general::rObj& obj, size_t beg = 0, size_t end = 0) -> uint32_t;
  };
}
