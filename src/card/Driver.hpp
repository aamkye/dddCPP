/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#pragma once

#include <card/Interface.hpp>
#include <structure/Driver.hpp>
#include <utils/ObjectConvertTool.hpp>
#include <iostream>
#include <json.hpp>
#include <vector>
#include <chroma.hpp>

using dataMap = std::map<uint32_t, ddd::structure::general::dataObj>;

namespace ddd {
  class Driver : public ddd::Interface {
  private:
    auto parseIcc(const bVec& binaryData) -> bool;
    auto parseIc(const bVec& binaryData) -> bool;
    auto parseDriverActivity(const bVec& binaryData) -> bool;
    auto parseEvents(const bVec& binaryData) -> bool;
    auto parseFaults(const bVec& binaryData) -> bool;
    auto parseAppIdentification(const bVec& binaryData) -> bool;
    auto parseControlActivity(const bVec& binaryData) -> bool;
    auto parseIdentification(const bVec& binaryData) -> bool;
    auto parsePlaces(const bVec& binaryData) -> bool;
    auto parseSpecificConditions(const bVec& binaryData) -> bool;
    auto parseVehiclesUsed(const bVec& binaryData) -> bool;
    auto parseCaCert(const bVec& binaryData) -> bool;
    auto parseCardCert(const bVec& binaryData) -> bool;
    auto proceed() -> bool;
    ddd::ObjectConvertTool convertTool;

  public:
    auto toJson(const std::string& outFile, const bool& readable) const -> bool;

    ddd::structure::ef::ICC                 icc;
    ddd::structure::ef::IC                  ic;
    ddd::structure::ef::APP_IDENTIFICATION  appId;
    ddd::structure::ef::IDENTIFICATION      idCard;
    ddd::structure::ef::CONTROL_ACTIVITY    controlActivity;
    ddd::structure::ef::DRIVER_ACTIVITY     driverActivity;
    ddd::structure::ef::VEHICLES_USED       vehiclesUsed;
    ddd::structure::ef::PLACES              places;
    ddd::structure::ef::CARD_CERT           cardCert;
    ddd::structure::ef::CA_CERT             caCert;
    ddd::structure::ef::EVENTS              events;
    ddd::structure::ef::FAULTS              faults;
    ddd::structure::ef::SPECIFIC_CONDITIONS specificConditions;

    dataMap data;
    dataMap cert;
    Driver(dataMap data, dataMap cert);
    virtual ~Driver();
    chroma::Operator chroma;
  };
}
