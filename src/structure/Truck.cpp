#include <nlohmann/json.hpp>
#include <structure/Truck.hpp>

auto ddd::structure::ed::OVERVIEW::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"vin", VIN.data},
    {"vehicleRegistrationNation", vehicleRegistrationNation.data},
    {"vehicleRegistrationNumber", vehicleRegistrationNumber.data},
    {"currentDateTime", currentDateTime.data},
    {"minDownloadableTime", minDownloadableTime.data},
    {"maxDownloadableTime", maxDownloadableTime.data},
    {"cardSlotsStatus", cardSlotsStatus.data},
    {"downloadingTime", downloadingTime.data},
    {"cardType", cardType.data},
    {"cardIssuingMemberState", cardIssuingMemberState.data},
    {"cardNumber", cardNumber.data},
    {"companyOrWorkshopName", companyOrWorkshopName.data},
    {"vuCompanyLocks", {}},
    {"vuControlActivity", {}}
  };

  for(auto const& x : vuCompanyLocks.records){
    nlohmann::json k = {
      {"lockInTime", x.lockInTime.data},
      {"lockOutTime", x.lockOutTime.data},
      {"companyName", x.companyName.data},
      {"companyAddress", x.companyAddress.data},
      {"cardType", x.cardType.data},
      {"cardIssuingMemberState", x.cardIssuingMemberState.data},
      {"cardNumber", x.cardNumber.data}};
    j["vuCompanyLocks"].push_back(k);
  }

  for(auto const& x : vuControlActivity.records){
    nlohmann::json k = {
      {"type", x.type.data},
      {"controlTime", x.controlTime.data},
      {"cardType", x.cardType.data},
      {"cardIssuingMemberState", x.cardIssuingMemberState.data},
      {"cardNumber", x.cardNumber.data},
      {"downloadPeriodBeginTime", x.downloadPeriodBeginTime.data},
      {"downloadPeriodEndTime", x.downloadPeriodEndTime.data}};
    j["vuControlActivity"].push_back(k);
  }

  return j;
}

auto ddd::structure::ed::ACTIVITIES::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"timeReal", timeReal.data},
    {"odometerValueMidnight", odometerValueMidnight.data},
    {"vuCardIW", {}},
    {"vuActivityDaily", {}},
    {"vuPlaceDailyWorkPeriod", {}},
    {"vuSpecificCondition", {}}
  };

  for(auto const& x : vuCardIW.records){
    nlohmann::json k = {
      {"holderSurname", x.holderSurname.data},
      {"holderFirstNames", x.holderFirstNames.data},
      {"cardType", x.cardType.data},
      {"cardIssuingMemberState", x.cardIssuingMemberState.data},
      {"cardNumber", x.cardNumber.data},
      {"cardExpiryDate", x.cardExpiryDate.data},
      {"cardInsertionTime", x.cardInsertionTime.data},
      {"vehicleOdometerValueAtInsertion", x.vehicleOdometerValueAtInsertion.data},
      {"cardSlotNumber", x.cardSlotNumber.data},
      {"cardWithdrawalTime", x.cardWithdrawalTime.data},
      {"vehicleOdometerValueAtWithdrawal", x.vehicleOdometerValueAtWithdrawal.data},
      {"vehicleRegistrationNation", x.vehicleRegistrationNation.data},
      {"vehicleRegistrationNumber", x.vehicleRegistrationNumber.data},
      {"previousCardWithdrawalTime", x.previousCardWithdrawalTime.data},
      {"manualInputFlag", x.manualInputFlag.data}};
    j["vuCardIW"].push_back(k);
  }

  for(auto const& x : vuActivityDaily.changes){
    nlohmann::json k = {
      {"slot", x.slot.data},
      {"crew", x.crew.data},
      {"placed", x.placed.data},
      {"activity", x.activity.data},
      {"time", x.time.data}};
    j["vuActivityDaily"].push_back(k);
  }

  for(auto const& x : vuPlaceDailyWorkPeriod.records){
    nlohmann::json k = {
      {"cardType", x.cardType.data},
      {"cardIssuingMemberState", x.cardIssuingMemberState.data},
      {"cardNumber", x.cardNumber.data},
      {"entryTime", x.entryTime.data},
      {"entryTypeDailyWorkPeriod", x.entryTypeDailyWorkPeriod.data},
      {"dailyWorkPeriodCountry", x.dailyWorkPeriodCountry.data},
      {"dailyWorkPeriodRegion", x.dailyWorkPeriodRegion.data},
      {"vehicleOdometerValue", x.vehicleOdometerValue.data}};
    j["vuPlaceDailyWorkPeriod"].push_back(k);
  }

  for(auto const& x : vuSpecificCondition.records){
    nlohmann::json k = {
      {"entryTime", x.entryTime.data},
      {"type", x.type.data}};
    j["vuSpecificCondition"].push_back(k);
  }

  return j;
}

auto ddd::structure::ed::EVENTS_AND_FAULTS::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"vuFault", {}},
    {"vuEvent", {}},
    {"lastOverspeedControlTime", lastOverspeedControlTime.data},
    {"firstOverspeedSince", firstOverspeedSince.data},
    {"numberOfOverspeedSince", numberOfOverspeedSince.data},
    {"vuOverSpeedingEvent", {}},
    {"vuTimeAdjustment", {}}};

  for(auto const& x : vuFault.faults){
    nlohmann::json k = {
      {"type", x.type.data},
      {"recordPurpose", x.recordPurpose.data},
      {"beginTime", x.beginTime.data},
      {"endTime", x.endTime.data},
      {"driverSlotBeginCardType", x.driverSlotBeginCardType.data},
      {"driverSlotBeginCardIssuingMemberState", x.driverSlotBeginCardIssuingMemberState.data},
      {"driverSlotBeginCardNumber", x.driverSlotBeginCardNumber.data},
      {"coDriverSlotBeginCardType", x.coDriverSlotBeginCardType.data},
      {"coDriverSlotBeginCardIssuingMemberState", x.coDriverSlotBeginCardIssuingMemberState.data},
      {"coDriverSlotBeginCardNumber", x.coDriverSlotBeginCardNumber.data},
      {"driverSlotEndCardType", x.driverSlotEndCardType.data},
      {"driverSlotEndCardIssuingMemberState", x.driverSlotEndCardIssuingMemberState.data},
      {"driverSlotEndCardNumber", x.driverSlotEndCardNumber.data},
      {"coDriverSlotEndCardType", x.coDriverSlotEndCardType.data},
      {"coDriverSlotEndCardIssuingMemberState", x.coDriverSlotEndCardIssuingMemberState.data},
      {"coDriverSlotEndCardNumber", x.coDriverSlotEndCardNumber.data}};
    j["vuFault"].push_back(k);
  }

  for(auto const& x : vuEvent.events){
    nlohmann::json k = {
      {"type", x.type.data},
      {"recordPurpose", x.recordPurpose.data},
      {"beginTime", x.beginTime.data},
      {"endTime", x.endTime.data},
      {"driverSlotBeginCardType", x.driverSlotBeginCardType.data},
      {"driverSlotBeginCardIssuingMemberState", x.driverSlotBeginCardIssuingMemberState.data},
      {"driverSlotBeginCardNumber", x.driverSlotBeginCardNumber.data},
      {"coDriverSlotBeginCardType", x.coDriverSlotBeginCardType.data},
      {"coDriverSlotBeginCardIssuingMemberState", x.coDriverSlotBeginCardIssuingMemberState.data},
      {"coDriverSlotBeginCardNumber", x.coDriverSlotBeginCardNumber.data},
      {"driverSlotEndCardType", x.driverSlotEndCardType.data},
      {"driverSlotEndCardIssuingMemberState", x.driverSlotEndCardIssuingMemberState.data},
      {"driverSlotEndCardNumber", x.driverSlotEndCardNumber.data},
      {"coDriverSlotEndCardType", x.coDriverSlotEndCardType.data},
      {"coDriverSlotEndCardIssuingMemberState", x.coDriverSlotEndCardIssuingMemberState.data},
      {"coDriverSlotEndCardNumber", x.coDriverSlotEndCardNumber.data},
      {"similarEventsNumber", x.similarEventsNumber.data}};
    j["vuEvent"].push_back(k);
  }

  for(auto const& x : vuOverSpeedingEvent.events){
    nlohmann::json k = {
      {"type", x.type.data},
      {"recordPurpose", x.recordPurpose.data},
      {"beginTime", x.beginTime.data},
      {"endTime", x.endTime.data},
      {"maxSpeedValue", x.maxSpeedValue.data},
      {"averageSpeedValue", x.averageSpeedValue.data},
      {"driverSlotBeginCardType", x.driverSlotBeginCardType.data},
      {"driverSlotBeginCardIssuingMemberState", x.driverSlotBeginCardIssuingMemberState.data},
      {"driverSlotBeginCardNumber", x.driverSlotBeginCardNumber.data},
      {"similarEventsNumber", x.similarEventsNumber.data}};
    j["vuOverSpeedingEvent"].push_back(k);
  }

  for(auto const& x : vuTimeAdjustment.records){
    nlohmann::json k = {
      {"oldTimeValue", x.oldTimeValue.data},
      {"newTimeValue", x.newTimeValue.data},
      {"workshopName", x.workshopName.data},
      {"workshopAddress", x.workshopAddress.data},
      {"workshopCardType", x.workshopCardType.data},
      {"workshopCardIssuingMemberState", x.workshopCardIssuingMemberState.data},
      {"workshopCardNumber", x.workshopCardNumber.data}};
    j["vuTimeAdjustment"].push_back(k);
  }

  return j;
}

auto ddd::structure::ed::DETAILED_SPEED::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"vuDeatailedSpeedBlock", {}}};

  for(auto const& x : vuDetailedSpeed.speedBlocks){
    nlohmann::json k = {
      {"speedBlockBeginDate", x.speedBlockBeginDate.data},
      {"records", {}}};

    for(auto const& y : x.records){
      nlohmann::json l = {
        {"record", y.speed.data}};
      k["records"].push_back(l);
    }

    j["vuDeatailedSpeedBlock"].push_back(k);
  }

  return j;
}

auto ddd::structure::ed::TECHNICAL_DATA::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"vuManufacturerName", vuManufacturerName.data},
    {"vuManufacturerAddress", vuManufacturerAddress.data},
    {"vuPartNumber", vuPartNumber.data},
    {"vuSerialNumber", {
      {"serialNumber", vuSerialNumber.serialNumber.data},
      {"monthYear", vuSerialNumber.monthYear.data},
      {"type", vuSerialNumber.type.data},
      {"manufacturerCode", vuSerialNumber.manufacturerCode.data}}},
    {"vuSoftwareVersion", vuSoftwareVersion.data},
    {"vuSoftInstallationDate", vuSoftInstallationDate.data},
    {"vuManufacturingDate", vuManufacturingDate.data},
    {"vuApprovalNumber", vuApprovalNumber.data},
    {"sensorSerialNumber", {
      {"serialNumber", sensorSerialNumber.serialNumber.data},
      {"monthYear", sensorSerialNumber.monthYear.data},
      {"type", sensorSerialNumber.type.data},
      {"manufacturerCode", sensorSerialNumber.manufacturerCode.data}}},
    {"sensorApprovalNumber", sensorApprovalNumber.data},
    {"sensorPairingDateFirst", sensorPairingDateFirst.data},
    {"vuCalibration", {}}};

  for(auto const& x : vuCalibration.records){
    nlohmann::json k = {
      {"calibrationPurpose", x.calibrationPurpose.data},
      {"workshopName", x.workshopName.data},
      {"workshopAddress", x.workshopAddress.data},
      {"workshopCardType", x.workshopCardType.data},
      {"workshopCardIssuingMemberState", x.workshopCardIssuingMemberState.data},
      {"workshopCardNumber", x.workshopCardNumber.data},
      {"workshopCardExpiryDate", x.workshopCardExpiryDate.data},
      {"VIN", x.VIN.data},
      {"vehicleRegistrationNation", x.vehicleRegistrationNation.data},
      {"vehicleRegistrationNumber", x.vehicleRegistrationNumber.data},
      {"wVehicleCharacteristicConstant", x.wVehicleCharacteristicConstant.data},
      {"kConstantOfRecordingEquipment", x.kConstantOfRecordingEquipment.data},
      {"lTyreCircumference", x.lTyreCircumference.data},
      {"tyreSize", x.tyreSize.data},
      {"authorisedSpeed", x.authorisedSpeed.data},
      {"oldOdometerValue", x.oldOdometerValue.data},
      {"newOdometerValue", x.newOdometerValue.data},
      {"oldTimeValue", x.oldTimeValue.data},
      {"newTimeValue", x.newTimeValue.data},
      {"nextCalibrationDate", x.nextCalibrationDate.data}};

    j["vuCalibration"].push_back(k);
  }

  return j;
}
