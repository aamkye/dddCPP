/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#include <card/Truck.hpp>
#include <utils/BVecHelper.hpp>
#include <structure/Truck.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>

ddd::Truck::~Truck(){}

ddd::Truck::Truck(
  std::map<uint32_t, std::vector<ddd::structure::general::dataObj>> vectorData)
  : vectorData(vectorData), chroma() {
  proceed();
}

auto ddd::Truck::parseOverview(const bVec& binaryData) -> bool {
  BVecHelper bVecHelper(binaryData);
  ddd::structure::ed::OVERVIEW obj;
  bVecHelper.extractAndParse(obj.memberStateCertificate, 194);
  bVecHelper.extractAndParse(obj.VUCertificate, 194);
  bVecHelper.extractAndParse(obj.VIN, 17);
  bVecHelper.extractAndParse(obj.vehicleRegistrationNation, 1);
  bVecHelper.extractAndParse(obj.vehicleRegistrationNumber, 14, 1);
  bVecHelper.extractAndParse(obj.currentDateTime, 4);
  bVecHelper.extractAndParse(obj.minDownloadableTime, 4);
  bVecHelper.extractAndParse(obj.maxDownloadableTime, 4);
  bVecHelper.extractAndParse(obj.cardSlotsStatus, 1);
  bVecHelper.extractAndParse(obj.downloadingTime, 4);
  bVecHelper.extractAndParse(obj.cardType, 1);
  bVecHelper.extractAndParse(obj.cardIssuingMemberState, 1);
  bVecHelper.extractAndParse(obj.cardNumber, 16);
  bVecHelper.extractAndParse(obj.companyOrWorkshopName, 36, 1);
  bVecHelper.extractAndParse(obj.vuCompanyLocks.noOfLocks, 1);
  for(uint32_t a = 0; a < obj.vuCompanyLocks.noOfLocks.data; ++a){
    ddd::structure::ed::OVERVIEW::vuCompanyLocks::record record;
    bVecHelper.extractAndParse(record.lockInTime, 4);
    bVecHelper.extractAndParse(record.lockOutTime, 4);
    bVecHelper.extractAndParse(record.companyName, 36, 1);
    bVecHelper.extractAndParse(record.companyAddress, 36, 1);
    bVecHelper.extractAndParse(record.cardType, 1);
    bVecHelper.extractAndParse(record.cardIssuingMemberState, 1);
    bVecHelper.extractAndParse(record.cardNumber, 16);
    obj.vuCompanyLocks.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.vuControlActivity.noOfControls, 1);
  for(uint32_t a = 0; a < obj.vuControlActivity.noOfControls.data; ++a){
    ddd::structure::ed::OVERVIEW::vuControlActivity::record record;
    bVecHelper.extractAndParse(record.type, 1);
    bVecHelper.extractAndParse(record.controlTime, 4);
    bVecHelper.extractAndParse(record.cardType, 1);
    bVecHelper.extractAndParse(record.cardIssuingMemberState, 1);
    bVecHelper.extractAndParse(record.cardNumber, 16);
    bVecHelper.extractAndParse(record.downloadPeriodBeginTime, 4);
    bVecHelper.extractAndParse(record.downloadPeriodEndTime, 4);
    obj.vuControlActivity.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.signature, 128);
  overview.push_back(obj);
  return true;
}

auto ddd::Truck::parseActivities(const bVec& binaryData) -> bool {
  BVecHelper bVecHelper(binaryData);
  ddd::structure::ed::ACTIVITIES obj;
  bVecHelper.extractAndParse(obj.timeReal, 4);
  bVecHelper.extractAndParse(obj.odometerValueMidnight, 3);
  bVecHelper.extractAndParse(obj.vuCardIW.noOfRecords, 2);
  for(uint32_t a = 0; a < obj.vuCardIW.noOfRecords.data; ++a){
    ddd::structure::ed::ACTIVITIES::vuCardIW::record record;
    bVecHelper.extractAndParse(record.holderSurname, 36, 1);
    bVecHelper.extractAndParse(record.holderFirstNames, 36, 1);
    bVecHelper.extractAndParse(record.cardType, 1);
    bVecHelper.extractAndParse(record.cardIssuingMemberState, 1);
    bVecHelper.extractAndParse(record.cardNumber, 16);
    bVecHelper.extractAndParse(record.cardExpiryDate, 4);
    bVecHelper.extractAndParse(record.cardInsertionTime, 4);
    bVecHelper.extractAndParse(record.vehicleOdometerValueAtInsertion, 3);
    bVecHelper.extractAndParse(record.cardSlotNumber, 1);
    bVecHelper.extractAndParse(record.cardWithdrawalTime, 4);
    bVecHelper.extractAndParse(record.vehicleOdometerValueAtWithdrawal, 3);
    bVecHelper.extractAndParse(record.vehicleRegistrationNation, 1);
    bVecHelper.extractAndParse(record.vehicleRegistrationNumber, 14, 1);
    bVecHelper.extractAndParse(record.previousCardWithdrawalTime, 4);
    bVecHelper.extractAndParse(record.manualInputFlag, 1);
    obj.vuCardIW.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.vuActivityDaily.noOfChanges, 2);
  for(uint32_t a = 0; a < obj.vuActivityDaily.noOfChanges.data; ++a){
    ddd::structure::ed::ACTIVITIES::vuActivityDaily::change change;
    bVecHelper.extractAndParse(change.raw, 2);
    std::string tempChange = convertTool.decToBin(convertTool.bitShift(change.raw.raw));
    change.slot.data       = convertTool.binToDec(tempChange.substr(0, 1));  // 1bit - slot
    change.crew.data       = convertTool.binToDec(tempChange.substr(1, 1));  // 1bit - crew
    change.placed.data     = convertTool.binToDec(tempChange.substr(2, 1));  // 1bit - placed
    change.activity.data   = convertTool.binToDec(tempChange.substr(3, 2));  // 2bites - activity
    change.time.data       = convertTool.binToDec(tempChange.substr(5, 11)); // 7bites - time
    obj.vuActivityDaily.changes.push_back(change);
  }

  bVecHelper.extractAndParse(obj.vuPlaceDailyWorkPeriod.noOfRecords, 1);
  for(uint32_t a = 0; a < obj.vuPlaceDailyWorkPeriod.noOfRecords.data; ++a){
    ddd::structure::ed::ACTIVITIES::vuPlaceDailyWorkPeriod::record record;
    bVecHelper.extractAndParse(record.cardType, 1);
    bVecHelper.extractAndParse(record.cardIssuingMemberState, 1);
    bVecHelper.extractAndParse(record.cardNumber, 16);
    bVecHelper.extractAndParse(record.entryTime, 4);
    bVecHelper.extractAndParse(record.entryTypeDailyWorkPeriod, 1);
    bVecHelper.extractAndParse(record.dailyWorkPeriodCountry, 1);
    bVecHelper.extractAndParse(record.dailyWorkPeriodRegion, 1);
    bVecHelper.extractAndParse(record.vehicleOdometerValue, 3);
    obj.vuPlaceDailyWorkPeriod.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.vuSpecificCondition.noOfRecords, 2);
  for(uint32_t a = 0; a < obj.vuSpecificCondition.noOfRecords.data; ++a){
    ddd::structure::ed::ACTIVITIES::vuSpecificCondition::record record;
    bVecHelper.extractAndParse(record.entryTime, 4);
    bVecHelper.extractAndParse(record.type, 1);
    obj.vuSpecificCondition.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.signature, 128);
  activities.push_back(obj);
  return true;
}

auto ddd::Truck::parseEventsAndFaults(const bVec& binaryData) -> bool {
  BVecHelper bVecHelper(binaryData);
  ddd::structure::ed::EVENTS_AND_FAULTS obj;
  bVecHelper.extractAndParse(obj.vuFault.noOfFaults, 1);
  for(uint32_t a = 0; a < obj.vuFault.noOfFaults.data; ++a){
    ddd::structure::ed::EVENTS_AND_FAULTS::vuFault::fault fault;
    bVecHelper.extractAndParse(fault.type, 1);
    bVecHelper.extractAndParse(fault.recordPurpose, 1);
    bVecHelper.extractAndParse(fault.beginTime, 4);
    bVecHelper.extractAndParse(fault.endTime, 4);
    bVecHelper.extractAndParse(fault.driverSlotBeginCardType, 1);
    bVecHelper.extractAndParse(fault.driverSlotBeginCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(fault.driverSlotBeginCardNumber, 16);
    bVecHelper.extractAndParse(fault.coDriverSlotBeginCardType, 1);
    bVecHelper.extractAndParse(fault.coDriverSlotBeginCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(fault.coDriverSlotBeginCardNumber, 16);
    bVecHelper.extractAndParse(fault.driverSlotEndCardType, 1);
    bVecHelper.extractAndParse(fault.driverSlotEndCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(fault.driverSlotEndCardNumber, 16);
    bVecHelper.extractAndParse(fault.coDriverSlotEndCardType, 1);
    bVecHelper.extractAndParse(fault.coDriverSlotEndCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(fault.coDriverSlotEndCardNumber, 16);
    obj.vuFault.faults.push_back(fault);
  }

  bVecHelper.extractAndParse(obj.vuEvent.noOfEvents, 1);
  for(uint32_t a = 0; a < obj.vuEvent.noOfEvents.data; ++a){
    ddd::structure::ed::EVENTS_AND_FAULTS::vuEvent::event event;
    bVecHelper.extractAndParse(event.type, 1);
    bVecHelper.extractAndParse(event.recordPurpose, 1);
    bVecHelper.extractAndParse(event.beginTime, 4);
    bVecHelper.extractAndParse(event.endTime, 4);
    bVecHelper.extractAndParse(event.driverSlotBeginCardType, 1);
    bVecHelper.extractAndParse(event.driverSlotBeginCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(event.driverSlotBeginCardNumber, 16);
    bVecHelper.extractAndParse(event.coDriverSlotBeginCardType, 1);
    bVecHelper.extractAndParse(event.coDriverSlotBeginCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(event.coDriverSlotBeginCardNumber, 16);
    bVecHelper.extractAndParse(event.driverSlotEndCardType, 1);
    bVecHelper.extractAndParse(event.driverSlotEndCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(event.driverSlotEndCardNumber, 16);
    bVecHelper.extractAndParse(event.coDriverSlotEndCardType, 1);
    bVecHelper.extractAndParse(event.coDriverSlotEndCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(event.coDriverSlotEndCardNumber, 16);
    bVecHelper.extractAndParse(event.similarEventsNumber, 1);
    obj.vuEvent.events.push_back(event);
  }

  bVecHelper.extractAndParse(obj.lastOverspeedControlTime, 4);
  bVecHelper.extractAndParse(obj.firstOverspeedSince, 4);
  bVecHelper.extractAndParse(obj.numberOfOverspeedSince, 1);
  bVecHelper.extractAndParse(obj.vuOverSpeedingEvent.noOfEvents, 1);
  for(uint32_t a = 0; a < obj.vuOverSpeedingEvent.noOfEvents.data; ++a){
    ddd::structure::ed::EVENTS_AND_FAULTS::vuOverSpeedingEvent::event event;
    bVecHelper.extractAndParse(event.type, 1);
    bVecHelper.extractAndParse(event.recordPurpose, 1);
    bVecHelper.extractAndParse(event.beginTime, 4);
    bVecHelper.extractAndParse(event.endTime, 4);
    bVecHelper.extractAndParse(event.maxSpeedValue, 1);
    bVecHelper.extractAndParse(event.averageSpeedValue, 1);
    bVecHelper.extractAndParse(event.driverSlotBeginCardType, 1);
    bVecHelper.extractAndParse(event.driverSlotBeginCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(event.driverSlotBeginCardNumber, 16);
    bVecHelper.extractAndParse(event.similarEventsNumber, 1);
    obj.vuOverSpeedingEvent.events.push_back(event);
  }

  bVecHelper.extractAndParse(obj.vuTimeAdjustment.noOfRecords, 1);
  for(uint32_t a = 0; a < obj.vuTimeAdjustment.noOfRecords.data; ++a){
    ddd::structure::ed::EVENTS_AND_FAULTS::vuTimeAdjustment::record record;
    bVecHelper.extractAndParse(record.oldTimeValue, 4);
    bVecHelper.extractAndParse(record.newTimeValue, 4);
    bVecHelper.extractAndParse(record.workshopName, 36);
    bVecHelper.extractAndParse(record.workshopAddress, 36);
    bVecHelper.extractAndParse(record.workshopCardType, 1);
    bVecHelper.extractAndParse(record.workshopCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(record.workshopCardNumber, 16);
    obj.vuTimeAdjustment.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.signature, 128);
  eventsAndFaults.push_back(obj);
  return true;
}

auto ddd::Truck::parseDetailedSpeed(const bVec& binaryData) -> bool {
  BVecHelper bVecHelper(binaryData);
  ddd::structure::ed::DETAILED_SPEED obj;

  bVecHelper.extractAndParse(obj.vuDetailedSpeed.noOfSpeedBlocks, 2);
  for(uint32_t a = 0; a < obj.vuDetailedSpeed.noOfSpeedBlocks.data; ++a){
    ddd::structure::ed::DETAILED_SPEED::vuDetailedSpeed::speedBlock speedBlock;
    bVecHelper.extractAndParse(speedBlock.speedBlockBeginDate, 4);

    ddd::structure::ed::DETAILED_SPEED::vuDetailedSpeed::speedBlock::record record;
    for(uint32_t a = 0; a != 60; a++){
      bVecHelper.extractAndParse(record.speed, 1);
      speedBlock.records.push_back(record);
    }

    obj.vuDetailedSpeed.speedBlocks.push_back(speedBlock);
  }

  bVecHelper.extractAndParse(obj.signature, 128);
  detailedSpeed.push_back(obj);
  return true;
}

auto ddd::Truck::parseTechnicalData(const bVec& binaryData) -> bool {
  BVecHelper bVecHelper(binaryData);
  ddd::structure::ed::TECHNICAL_DATA obj;

  bVecHelper.extractAndParse(obj.vuManufacturerName, 36, 1);
  bVecHelper.extractAndParse(obj.vuManufacturerAddress, 36, 1);
  bVecHelper.extractAndParse(obj.vuPartNumber, 16);
  bVecHelper.extractAndParse(obj.vuSerialNumber.serialNumber, 4);
  bVecHelper.extractAndParse(obj.vuSerialNumber.monthYear, 2);
  bVecHelper.extractAndParse(obj.vuSerialNumber.type, 1);
  bVecHelper.extractAndParse(obj.vuSerialNumber.manufacturerCode, 1);
  bVecHelper.extractAndParse(obj.vuSoftwareVersion, 4);
  bVecHelper.extractAndParse(obj.vuSoftInstallationDate, 4);
  bVecHelper.extractAndParse(obj.vuManufacturingDate, 4);
  bVecHelper.extractAndParse(obj.vuApprovalNumber, 8);
  bVecHelper.extractAndParse(obj.sensorSerialNumber.serialNumber, 4);
  bVecHelper.extractAndParse(obj.sensorSerialNumber.monthYear, 2);
  bVecHelper.extractAndParse(obj.sensorSerialNumber.type, 1);
  bVecHelper.extractAndParse(obj.sensorSerialNumber.manufacturerCode, 1);
  bVecHelper.extractAndParse(obj.sensorApprovalNumber, 8);
  bVecHelper.extractAndParse(obj.sensorPairingDateFirst, 4);

  bVecHelper.extractAndParse(obj.vuCalibration.noOfRecords, 1);
  for(uint32_t a = 0; a < obj.vuCalibration.noOfRecords.data; ++a){
    ddd::structure::ed::TECHNICAL_DATA::vuCalibration::record record;
    bVecHelper.extractAndParse(record.calibrationPurpose, 1);
    bVecHelper.extractAndParse(record.workshopName, 36, 1);
    bVecHelper.extractAndParse(record.workshopAddress, 36, 1);
    bVecHelper.extractAndParse(record.workshopCardType, 1);
    bVecHelper.extractAndParse(record.workshopCardIssuingMemberState, 1);
    bVecHelper.extractAndParse(record.workshopCardNumber, 16);
    bVecHelper.extractAndParse(record.workshopCardExpiryDate, 4);
    bVecHelper.extractAndParse(record.VIN, 17);
    bVecHelper.extractAndParse(record.vehicleRegistrationNation, 1);
    bVecHelper.extractAndParse(record.vehicleRegistrationNumber, 14, 1);
    bVecHelper.extractAndParse(record.wVehicleCharacteristicConstant, 2);
    bVecHelper.extractAndParse(record.kConstantOfRecordingEquipment, 2);
    bVecHelper.extractAndParse(record.lTyreCircumference, 2);
    bVecHelper.extractAndParse(record.tyreSize, 15);
    bVecHelper.extractAndParse(record.authorisedSpeed, 1);
    bVecHelper.extractAndParse(record.oldOdometerValue, 3);
    bVecHelper.extractAndParse(record.newOdometerValue, 3);
    bVecHelper.extractAndParse(record.oldTimeValue, 4);
    bVecHelper.extractAndParse(record.newTimeValue, 4);
    bVecHelper.extractAndParse(record.nextCalibrationDate, 4);
    obj.vuCalibration.records.push_back(record);
  }

  bVecHelper.extractAndParse(obj.signature, 128);
  technicalData.push_back(obj);
  return true;
}

auto ddd::Truck::proceed() -> bool {
  for(const auto& entity : vectorData){
    switch(entity.first){
      case ddd::identificator::ed::OVERVIEW: {
        for(const auto& record : entity.second)
          parseOverview(record.raw);
      } break;
      case ddd::identificator::ed::ACTIVITIES: {
        for(const auto& record : entity.second)
          parseActivities(record.raw);
      } break;
      case ddd::identificator::ed::EVENTS_AND_FAULTS: {
        for(const auto& record : entity.second)
          parseEventsAndFaults(record.raw);
      } break;
      case ddd::identificator::ed::DETAILED_SPEED: {
        for(const auto& record : entity.second)
          parseDetailedSpeed(record.raw);
      } break;
      case ddd::identificator::ed::TECHNICAL_DATA: {
        for(const auto& record : entity.second)
          parseTechnicalData(record.raw);
      } break;
    }
  }
  return true;
}

auto ddd::Truck::toJson(const std::string& outFile = "", const bool& readable = false) const -> bool {
  nlohmann::json j;
  j["type"]            = "truck";
  j["overview"]        = {};
  j["activities"]      = {};
  j["eventsAndFaults"] = {};
  j["detailedSpeed"]   = {};
  j["technicalData"]   = {};

  for(const auto& entity : overview)
    j["overview"].push_back(entity.toJson());
  for(const auto& entity : activities)
    j["activities"].push_back(entity.toJson());
  for(const auto& entity : eventsAndFaults)
    j["eventsAndFaults"].push_back(entity.toJson());
  for(const auto& entity : detailedSpeed)
    j["detailedSpeed"].push_back(entity.toJson());
  for(const auto& entity : technicalData)
    j["technicalData"].push_back(entity.toJson());

  std::ofstream o(outFile, std::ios::binary);

  if(readable) {
    o << j.dump(2) << std::endl;
  } else {
    o << j.dump() << std::endl;
  }

  return true;
}
