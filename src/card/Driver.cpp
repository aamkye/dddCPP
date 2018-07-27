/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#include <card/Driver.hpp>
#include <utils/BVecHelper.hpp>
#include <structure/Driver.hpp>
#include <Chroma.hpp>
#include <iostream>
#include <json.hpp>
#include <vector>
#include <fstream>

ddd::Driver::Driver(std::map<uint32_t, ddd::structure::general::dataObj> data)
  : convertTool(), data(data), chroma() {
  proceed();
}

ddd::Driver::~Driver() {}

bool ddd::Driver::parseIcc(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(icc.clockStop, 1);
  bVecHelper.extractAndParse(icc.extendedSerialNumber.serialNumber, 4);
  bVecHelper.extractAndParse(icc.extendedSerialNumber.monthYear, 2);
  bVecHelper.extractAndParse(icc.extendedSerialNumber.type, 1);
  bVecHelper.extractAndParse(icc.extendedSerialNumber.manufacturerCode, 1);
  bVecHelper.extractAndParse(icc.cardApprovalNumber, 8);
  bVecHelper.extractAndParse(icc.cardPersonalID, 1);
  bVecHelper.extractAndParse(icc.embedderIcAssemblerID, 5);
  bVecHelper.extractAndParse(icc.icIdentifier, 2);
  uint32_t month = convertTool.parseBCD(icc.extendedSerialNumber.monthYear, 0, 1);
  uint32_t year  = convertTool.parseBCD(icc.extendedSerialNumber.monthYear, 1, 2);
  icc.extendedSerialNumber.monthYear.data = std::to_string(month) + "/" + std::to_string(year);
  return true;
}

bool ddd::Driver::parseIc(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(ic.serialNumber, 4);
  bVecHelper.extractAndParse(ic.manufacturingReferences, 4);
  return true;
}

bool ddd::Driver::parseAppIdentification(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(appId.typeOfTachographCardId, 1);
  bVecHelper.extractAndParse(appId.cardStructureVersion, 2);
  bVecHelper.extractAndParse(appId.noOfEventsPerType, 1);
  bVecHelper.extractAndParse(appId.noOfFaultsPerType, 1);
  bVecHelper.extractAndParse(appId.activityStructureLength, 2);
  bVecHelper.extractAndParse(appId.noOfCardVehicleRecords, 2);
  bVecHelper.extractAndParse(appId.noOfCardPlaceRecords, 1);
  return true;
}

bool ddd::Driver::parseControlActivity(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(controlActivity.type, 1);
  bVecHelper.extractAndParse(controlActivity.time, 4);
  bVecHelper.extractAndParse(controlActivity.cardType, 1);
  bVecHelper.extractAndParse(controlActivity.cardIssuingMemberState, 1);
  bVecHelper.extractAndParse(controlActivity.cardNumber, 16);
  bVecHelper.extractAndParse(controlActivity.vehicleRegistrationNation, 1);
  bVecHelper.extractAndParse(controlActivity.vehicleRegistrationNumber, 14, 1);
  bVecHelper.extractAndParse(controlActivity.downloadPeriodBegin, 4);
  bVecHelper.extractAndParse(controlActivity.downloadPeriodEnd, 4);
  return true;
}

bool ddd::Driver::parseSpecificConditions(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  do {
    ddd::structure::ef::SPECIFIC_CONDITIONS::record data;
    bVecHelper.extractAndParse(data.entryTime, 4);
    bVecHelper.extractAndParse(data.type, 1);
    specificConditions.records.push_back(data);
  } while(data[ddd::identificator::ef::SPECIFIC_CONDITIONS].length.data > bVecHelper.getOffSet());
  return true;
}

bool ddd::Driver::parseEvents(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  do {
    ddd::structure::ef::EVENTS::record data;
    bVecHelper.extractAndParse(data.type, 1);
    bVecHelper.extractAndParse(data.beginTime, 4);
    bVecHelper.extractAndParse(data.endTime, 4);
    bVecHelper.extractAndParse(data.vehicleRegistrationNation, 1);
    bVecHelper.extractAndParse(data.vehicleRegistrationNumber, 14, 1);
    events.records.push_back(data);
  } while(data[ddd::identificator::ef::EVENTS].length.data > bVecHelper.getOffSet());
  return true;
}

bool ddd::Driver::parseFaults(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  do {
    ddd::structure::ef::FAULTS::record data;
    bVecHelper.extractAndParse(data.type, 1);
    bVecHelper.extractAndParse(data.beginTime, 4);
    bVecHelper.extractAndParse(data.endTime, 4);
    bVecHelper.extractAndParse(data.vehicleRegistrationNation, 1);
    bVecHelper.extractAndParse(data.vehicleRegistrationNumber, 14, 1);
    faults.records.push_back(data);
  } while(data[ddd::identificator::ef::FAULTS].length.data > bVecHelper.getOffSet());
  return true;
}

bool ddd::Driver::parseIdentification(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(idCard.issuingMemberState, 1);
  bVecHelper.extractAndParse(idCard.number, 16);
  bVecHelper.extractAndParse(idCard.issuingAuthorityName, 36, 1);
  bVecHelper.extractAndParse(idCard.issueDate, 4);
  bVecHelper.extractAndParse(idCard.validityBegin, 4);
  bVecHelper.extractAndParse(idCard.expiryDate, 4);
  bVecHelper.extractAndParse(idCard.holderSurname, 36, 1);
  bVecHelper.extractAndParse(idCard.holderFirstNames, 36, 1);
  bVecHelper.extractAndParse(idCard.holderBirthDate, 4);
  bVecHelper.extractAndParse(idCard.holderPreferredLanguage, 2);
  uint32_t a = convertTool.parseBCD(idCard.holderBirthDate, 0, 1);
  uint32_t b = convertTool.parseBCD(idCard.holderBirthDate, 1, 2);
  uint32_t c = convertTool.parseBCD(idCard.holderBirthDate, 2, 3);
  uint32_t d = convertTool.parseBCD(idCard.holderBirthDate, 3, 4);
  idCard.holderBirthDate.data = std::to_string(d) + "/" + std::to_string(c) + "/" + std::to_string(a) + std::to_string(b);
  convertTool.parse(idCard.holderPreferredLanguage);
  return true;
}

bool ddd::Driver::parsePlaces(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(places.PNR, 1);
  uint32_t newest = places.PNR.data * 10;
  uint32_t placesRecordStructureLength = appId.noOfCardPlaceRecords.data * 10;
  bVec placesRecords = bVecHelper.genericExtract(placesRecordStructureLength);
  bVecHelper.reorderUnsortedBVec(
    placesRecords,
    newest,
    placesRecordStructureLength,
    10);
  bVecHelper.bVecData = placesRecords;
  bVecHelper.resetOffset();
  bVecHelper.getOffSet(newest);
  uint32_t offset = 0;
  do {
    offset = bVecHelper.getOffSet();
    ddd::structure::ef::PLACES::record data;
    bVecHelper.extractAndParse(data.entryTime, 4);
    bVecHelper.extractAndParse(data.entryTypeDailyWorkPeriod, 1);
    bVecHelper.extractAndParse(data.dailyWorkPeriodCountry, 1);
    bVecHelper.extractAndParse(data.dailyWorkPeriodRegion, 1);
    bVecHelper.extractAndParse(data.vehicleOdometerValue, 3);
    places.records.push_back(data);
    bVecHelper.resetOffset();
    bVecHelper.getOffSet(offset - 10);
  } while(0 != bVecHelper.getOffSet());
  return true;
}

bool ddd::Driver::parseVehiclesUsed(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(vehiclesUsed.PNR, 2);
  uint32_t newest = vehiclesUsed.PNR.data * 31;
  uint32_t vehicleRecordStructureLength = appId.noOfCardVehicleRecords.data * 31;
  bVec vehicleRecord = bVecHelper.genericExtract(vehicleRecordStructureLength);
  bVecHelper.reorderUnsortedBVec(
    vehicleRecord,
    newest,
    vehicleRecordStructureLength,
    31);
  bVecHelper.bVecData = vehicleRecord;
  bVecHelper.resetOffset();
  bVecHelper.getOffSet(newest);
  uint32_t offset = 0;
  do {
    ddd::structure::ef::VEHICLES_USED::record data;
    offset = bVecHelper.getOffSet();
    bVecHelper.extractAndParse(data.odometerBegin, 3);
    bVecHelper.extractAndParse(data.odometerEnd, 3);
    bVecHelper.extractAndParse(data.firstUse, 4);
    bVecHelper.extractAndParse(data.lastUse, 4);
    bVecHelper.extractAndParse(data.registrationNation, 1);
    bVecHelper.extractAndParse(data.registrationNumber, 14, 1);
    bVecHelper.extractAndParse(data.vuDataBlockCounter, 2);
    uint32_t a = convertTool.parseBCD(data.vuDataBlockCounter, 0, 1);
    uint32_t b = convertTool.parseBCD(data.vuDataBlockCounter, 1, 2);
    data.vuDataBlockCounter.data = a * 100 + b;
    vehiclesUsed.records.push_back(data);
    bVecHelper.resetOffset();
    bVecHelper.getOffSet(offset - 31);
  } while(0 != bVecHelper.getOffSet());
  return true;
}

bool ddd::Driver::parseDriverActivity(const bVec& binaryData) {
  BVecHelper bVecHelper(binaryData);
  bVecHelper.extractAndParse(driverActivity.POR, 2);
  bVecHelper.extractAndParse(driverActivity.PNR, 2);
  uint32_t newest = driverActivity.PNR.data;
  uint32_t oldest = driverActivity.POR.data;
  uint32_t activityStructureLength = appId.activityStructureLength.data;
  bVec activityDailyRecord = bVecHelper.genericExtract(activityStructureLength);
  bVecHelper.reorderOldBVec(activityDailyRecord, newest, oldest, activityStructureLength);
  bVecHelper.bVecData = activityDailyRecord;
  bVecHelper.resetOffset();
  bVecHelper.getOffSet(newest);
  uint32_t offset = 0;
  uint32_t lastPreviousRecordLength = 0;
  do {
    offset = bVecHelper.getOffSet();
    ddd::structure::ef::DRIVER_ACTIVITY::daily dailyData;
    bVecHelper.extractAndParse(dailyData.previousRecordLength, 2);
    bVecHelper.extractAndParse(dailyData.recordDate, 6);
    bVecHelper.extractAndParse(dailyData.dailyPresenceCounter, 2);
    bVecHelper.extractAndParse(dailyData.dayDistance, 2);
    uint32_t a = convertTool.parseBCD(dailyData.dailyPresenceCounter, 0, 1);
    uint32_t b = convertTool.parseBCD(dailyData.dailyPresenceCounter, 1, 2);
    dailyData.dailyPresenceCounter.data = a * 100 + b;
    auto f1 = [&, this]() {
      ddd::structure::ef::DRIVER_ACTIVITY::daily::change changeData;
      bVecHelper.extractAndParse(changeData.raw, 2);
      std::string tempDailyRecord = convertTool.decToBin(convertTool.bitShift(changeData.raw.raw));
      changeData.slot.data        = convertTool.binToDec(tempDailyRecord.substr(0, 1));  // 1bit - slot
      changeData.crew.data        = convertTool.binToDec(tempDailyRecord.substr(1, 1));  // 1bit - crew
      changeData.placed.data      = convertTool.binToDec(tempDailyRecord.substr(2, 1));  // 1bit - placed
      changeData.activity.data    = convertTool.binToDec(tempDailyRecord.substr(3, 2));  // 2bites - activity
      changeData.time.data        = convertTool.binToDec(tempDailyRecord.substr(5, 11)); // 7bites - time
      dailyData.changes.push_back(changeData);
    };
    uint32_t limiter = 0;
    lastPreviousRecordLength != 0 ?
      limiter = offset + lastPreviousRecordLength :
      limiter = activityStructureLength;
    do {
      f1();
    } while(limiter > bVecHelper.getOffSet());
    driverActivity.dailyChange.push_back(dailyData);
    lastPreviousRecordLength = dailyData.previousRecordLength.data;
    bVecHelper.resetOffset();
    bVecHelper.getOffSet(offset - lastPreviousRecordLength);
  } while(0 < bVecHelper.getOffSet());
  return true;
}

bool ddd::Driver::proceed() {
  for(const auto& entity : data) {
    switch(entity.first) {
      case ddd::identificator::ef::ICC:
        parseIcc(entity.second.raw); break;
      case ddd::identificator::ef::IC:
        parseIc(entity.second.raw); break;
      case ddd::identificator::ef::APP_IDENTIFICATION:
        parseAppIdentification(entity.second.raw); break;
      case ddd::identificator::ef::EVENTS:
        parseEvents(entity.second.raw); break;
      case ddd::identificator::ef::IDENTIFICATION:
        parseIdentification(entity.second.raw); break;
      case ddd::identificator::ef::FAULTS:
        parseFaults(entity.second.raw); break;
      case ddd::identificator::ef::DRIVER_ACTIVITY:
        parseDriverActivity(entity.second.raw); break;
      case ddd::identificator::ef::VEHICLES_USED:
        parseVehiclesUsed(entity.second.raw); break;
      case ddd::identificator::ef::PLACES:
        parsePlaces(entity.second.raw); break;
      case ddd::identificator::ef::CONTROL_ACTIVITY:
        parseControlActivity(entity.second.raw); break;
      case ddd::identificator::ef::SPECIFIC_CONDITIONS:
        parseSpecificConditions(entity.second.raw); break;
      case ddd::identificator::ef::CARD_CERT: break;
      case ddd::identificator::ef::CA_CERT: break;
      default: break;
    }
  }
  return true;
}

bool ddd::Driver::toJson(const std::string& outFile = "", const bool& readable = false) const {
  nlohmann::json j;
  j["type"]                   = "driver";
  j["iccData"]                = icc.toJson();
  j["icData"]                 = ic.toJson();
  j["appIdData"]              = appId.toJson();
  j["controlActivityData"]    = controlActivity.toJson();
  j["specificConditionsData"] = specificConditions.toJson();
  j["eventsData"]             = events.toJson();
  j["faultsData"]             = faults.toJson();
  j["idData"]                 = idCard.toJson();
  j["placesData"]             = places.toJson();
  j["vehiclesUsedData"]       = vehiclesUsed.toJson();
  j["driverActivityData"]     = driverActivity.toJson();

  std::ofstream o(outFile, std::ios::binary);

  if(readable) {
    o << j.dump(2) << std::endl;
  } else {
    o << j.dump() << std::endl;
  }
  return true;
}
