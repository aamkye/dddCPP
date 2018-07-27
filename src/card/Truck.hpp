/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#pragma once

#include <card/Interface.hpp>
#include <structure/Truck.hpp>
#include <utils/ObjectConvertTool.hpp>
#include <Chroma.hpp>
#include <iostream>
#include <json.hpp>
#include <vector>

namespace ddd {
  class Truck : public ddd::Interface {
  private:
    auto parseOverview(const bVec& binaryData) -> bool;
    auto parseActivities(const bVec& binaryData) -> bool;
    auto parseEventsAndFaults(const bVec& binaryData) -> bool;
    auto parseDetailedSpeed(const bVec& binaryData) -> bool;
    auto parseTechnicalData(const bVec& binaryData) -> bool;
    auto proceed() -> bool;
    ddd::ObjectConvertTool convertTool;

  public:
    auto toJson(
      const std::string& outFile,
      const bool& readable) const -> bool;

    std::vector<ddd::structure::ed::OVERVIEW> overview;
    std::vector<ddd::structure::ed::ACTIVITIES> activities;
    std::vector<ddd::structure::ed::EVENTS_AND_FAULTS> eventsAndFaults;
    std::vector<ddd::structure::ed::DETAILED_SPEED> detailedSpeed;
    std::vector<ddd::structure::ed::TECHNICAL_DATA> technicalData;

    std::map<uint32_t, std::vector<ddd::structure::general::dataObj>> vectorData;
    Truck(std::map<uint32_t, std::vector<ddd::structure::general::dataObj>> vectorData);
    virtual ~Truck();
    chroma::Painter chroma;
  };
}
