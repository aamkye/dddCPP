#pragma once

#include <utils/ObjectConvertTool.hpp>
#include <structure/General.hpp>
#include <iostream>
#include <vector>

namespace ddd
{
  class BVecHelper
  {
  public:
    BVecHelper();
    BVecHelper(const bVec& data);
    uint32_t offSet = 0;
    bVec     bVecData;
    ddd::ObjectConvertTool convertTool;

    auto resetOffset() -> void;
    auto getOffSet() const -> uint32_t;
    auto getOffSet(
      const uint32_t& val) -> uint32_t;
    auto getReverseOffSet(
      const uint32_t& val) -> uint32_t;

    auto reorderOldBVec(
      bVec&     obj,
      uint32_t& newest,
      uint32_t& oldest,
      uint32_t& len) -> void;
    auto reorderUnsortedBVec(
      bVec&      obj,
      uint32_t&  newest,
      uint32_t&  len,
      uint32_t&& offset) -> void;
    auto extract(
      ddd::structure::general::rObj& obj,
      const size_t& offset) -> void;
    auto genericExtract(
      const size_t& offset) -> bVec;

    template<typename T>
    auto extractAndParse(
      T& obj,
      const size_t& offset,
      const size_t& parseOffset = 0) -> void
    {
      obj.raw = genericExtract(offset);
      convertTool.parse(obj, parseOffset);
    }
  };
}
