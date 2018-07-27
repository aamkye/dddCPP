/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#include <utils/BVecHelper.hpp>
#include <structure/General.hpp>
#include <fstream>
#include <iostream>
#include <vector>

ddd::BVecHelper::BVecHelper() {
  resetOffset();
}

ddd::BVecHelper::BVecHelper(const bVec& data) : bVecData(data) {
  resetOffset();
}

auto ddd::BVecHelper::resetOffset() -> void {
  offSet = 0;
}

auto ddd::BVecHelper::getOffSet() const -> uint32_t {
  return offSet;
}

auto ddd::BVecHelper::getOffSet(const uint32_t& val) -> uint32_t {
  offSet += val;
  return getOffSet();
}

auto ddd::BVecHelper::getReverseOffSet(const uint32_t& val) -> uint32_t {
  offSet -= val;
  return getOffSet();
}

auto ddd::BVecHelper::reorderOldBVec(bVec& obj, uint32_t& newest, uint32_t& oldest, uint32_t& len) -> void {
  if(newest < oldest) {
    bVec newObj;
    newObj.reserve(obj.size());
    newObj.insert(newObj.end(), obj.begin() + oldest, obj.begin() + len);
    newObj.insert(newObj.end(), obj.begin(), obj.begin() + oldest);
    obj    = newObj;
    newest = len - oldest + newest;
  }
}

auto ddd::BVecHelper::reorderUnsortedBVec(bVec& obj, uint32_t& newest, uint32_t& len, uint32_t&& offset) -> void {
  if(newest != 0) {
    bVec newObj;
    newObj.reserve(obj.size());
    newObj.insert(newObj.end(), obj.begin() + newest + offset, obj.begin() + len);
    newObj.insert(newObj.end(), obj.begin(), obj.begin() + newest + offset);
    obj = newObj;

    newest = len - offset;
  }
}

auto ddd::BVecHelper::genericExtract(const size_t& offset) -> bVec {
  std::vector<u_int8_t>::iterator beg = bVecData.begin() + getOffSet();
  std::vector<u_int8_t>::iterator end = bVecData.begin() + getOffSet(offset);
  // GCC7.3.0 issue, cannot pass beg and end inline
  return bVec(beg, end);
}

auto ddd::BVecHelper::extract(
  ddd::structure::general::rObj& obj,
  const size_t& offset) -> void
{
  obj.raw = genericExtract(offset);
}
