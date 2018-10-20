/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#pragma once

#include <utils/IOHandler.hpp>
#include <utils/ObjectConvertTool.hpp>
#include <structure/General.hpp>
#include <chroma.hpp>
#include <iostream>
#include <map>
#include <vector>

namespace ddd {
  class Raw {
  public:
    std::map<uint32_t, ddd::structure::general::dataObj> data;
    std::map<uint32_t, std::vector<ddd::structure::general::dataObj>> vectorData;
    std::map<uint32_t, ddd::structure::general::dataObj> certData;
    Raw();
    Raw(std::string _name);
    virtual ~Raw();

    uint32_t cardType = -1;
    const uint32_t certLen = 128;
    ddd::IOHandler ioHandler;
    ddd::ObjectConvertTool convertTool;
    chroma::Operator chroma;

  private:
    bool proceed();
    bool readDriverStructure(const bVec &rawId);
    bool readTruckStructure(const bVec &rawId);
  };
}
