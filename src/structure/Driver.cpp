#include <json.hpp>
#include <structure/Driver.hpp>

auto ddd::structure::ef::ICC::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"clockStop", clockStop.data},
    {"cardExtendedSerialNumber",
     {{"manufacturerCode", extendedSerialNumber.manufacturerCode.data},
      {"monthYear", extendedSerialNumber.monthYear.data},
      {"serialNumber", extendedSerialNumber.serialNumber.data},
      {"type", extendedSerialNumber.type.data}}},
    {"embedderIcAssemblerID", embedderIcAssemblerID.data},
    {"icIdentifier", icIdentifier.data},
    {"cardPersonalID", cardPersonalID.data},
    {"cardApprovalNumber", cardApprovalNumber.data}};
  return j;
}

auto ddd::structure::ef::IC::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"icSerialNumber", serialNumber.data},
    {"icManufacturingReferences", manufacturingReferences.data}};
  return j;
}

auto ddd::structure::ef::APP_IDENTIFICATION::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"typeOfTachographCardId", typeOfTachographCardId.data},
    {"cardStructureVersion", cardStructureVersion.data},
    {"noOfEventsPerType", noOfEventsPerType.data},
    {"noOfFaultsPerType", noOfFaultsPerType.data},
    {"activityStructureLength", activityStructureLength.data},
    {"noOfCardVehicleRecords", noOfCardVehicleRecords.data},
    {"noOfCardPlaceRecords", noOfCardPlaceRecords.data}};
  return j;
}

auto ddd::structure::ef::CONTROL_ACTIVITY::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"controlType", type.data},
    {"controlTime", time.data},
    {"cardType", cardType.data},
    {"cardIssuingMemberState", cardIssuingMemberState.data},
    {"cardNumber", cardNumber.data},
    {"vehicleRegistrationNation", vehicleRegistrationNation.data},
    {"vehicleRegistrationNumber", vehicleRegistrationNumber.data},
    {"controlDownloadPeriodBegin", downloadPeriodBegin.data},
    {"controlDownloadPeriodEnd", downloadPeriodEnd.data}};
  return j;
}

auto ddd::structure::ef::SPECIFIC_CONDITIONS::toJson() const -> nlohmann::json {
  nlohmann::json j = {};
  for(auto const& x : records){
    nlohmann::json k = {
      {"entryTime", x.entryTime.data},
      {"specificConditionType", x.type.data}};
    j.push_back(k);
  }
  return j;
}

auto ddd::structure::ef::EVENTS::toJson() const -> nlohmann::json {
  nlohmann::json j = {};
  for(auto const& x : records){
    nlohmann::json k = {
      {"eventType", x.type.data},
      {"eventBeginTime", x.beginTime.data},
      {"eventEndTime", x.endTime.data},
      {"vehicleRegistrationNation", x.vehicleRegistrationNation.data},
      {"vehicleRegistrationNumber", x.vehicleRegistrationNumber.data}};
    j.push_back(k);
  }
  return j;
}

auto ddd::structure::ef::FAULTS::toJson() const -> nlohmann::json {
  nlohmann::json j = {};
  for(auto const& x : records){
    nlohmann::json k = {
      {"eventType", x.type.data},
      {"eventBeginTime", x.beginTime.data},
      {"eventEndTime", x.endTime.data},
      {"vehicleRegistrationNation", x.vehicleRegistrationNation.data},
      {"vehicleRegistrationNumber", x.vehicleRegistrationNumber.data}};
    j.push_back(k);
  }
  return j;
}

auto ddd::structure::ef::IDENTIFICATION::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"cardIssuingMemberState", issuingMemberState.data},
    {"cardNumber", number.data},
    {"cardIssuingAuthorityName", issuingAuthorityName.data},
    {"cardIssueDate", issueDate.data},
    {"cardValidityBegin", validityBegin.data},
    {"cardExpiryDate", expiryDate.data},
    {"holderSurname", holderSurname.data},
    {"holderFirstNames", holderFirstNames.data},
    {"cardHolderBirthDate", holderBirthDate.data},
    {"cardHolderPreferredLanguage", holderPreferredLanguage.data}};
  return j;
}

auto ddd::structure::ef::PLACES::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"placePointerNewestRecord", PNR.data},
    {"placesRecord", {}}};

  for(auto const& x : records){
    nlohmann::json k = {
      {"entryTime", x.entryTime.data},
      {"entryTypeDailyWorkPeriod", x.entryTypeDailyWorkPeriod.data},
      {"dailyWorkPeriodCountry", x.dailyWorkPeriodCountry.data},
      {"dailyWorkPeriodRegion", x.dailyWorkPeriodRegion.data},
      {"vehicleOdometerValue", x.vehicleOdometerValue.data}};
    j["placesRecord"].push_back(k);
  }
  return j;
}

auto ddd::structure::ef::VEHICLES_USED::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"vehiclePointerNewestRecord", PNR.data},
    {"vehicleRecord", {}}};
  for(auto const& x : records){
    nlohmann::json k = {
      {"vehicleOdometerBegin", x.odometerBegin.data},
      {"vehicleOdometerEnd", x.odometerEnd.data},
      {"vehicleFirstUse", x.firstUse.data},
      {"vehicleLastUse", x.lastUse.data},
      {"vehicleRegistrationNation", x.registrationNation.data},
      {"vehicleRegistrationNumber", x.registrationNumber.data},
      {"vuDataBlockCounter", x.vuDataBlockCounter.data}};
    j["vehicleRecord"].push_back(k);
  }
  return j;
}

auto ddd::structure::ef::DRIVER_ACTIVITY::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"activityPointerOldestDayRecord", POR.data},
    {"activityPointerNewestRecord", PNR.data},
    {"activityDaily", {}}};
  for(auto const& x : dailyChange){
    nlohmann::json l;
    for(auto const& y : x.changes){
      l.push_back(
        {{"slot", y.slot.data},
         {"crew", y.crew.data},
         {"placed", y.placed.data},
         {"activity", y.activity.data},
         {"time", y.time.data}});
    }

    nlohmann::json k = {
      {"previousRecordLength", x.previousRecordLength.data},
      {"recordDate", x.recordDate.data},
      {"dailyPresenceCounter", x.dailyPresenceCounter.data},
      {"dayDistance", x.dayDistance.data},
      {"changeInfo", l}};
    j["activityDaily"].push_back(k);
  }
  return j;
}

auto ddd::structure::ef::CA_CERT::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"valid", valid.data},
    {"cert", cert.data}};
  return j;
}

auto ddd::structure::ef::CARD_CERT::toJson() const -> nlohmann::json {
  nlohmann::json j = {
    {"valid", valid.data},
    {"cert", cert.data}};
  return j;
}
