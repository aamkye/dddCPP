/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#pragma once

#include <json.hpp>
#include <structure/General.hpp>

namespace ddd {
  namespace structure {
    namespace ef {
      struct ICC : public general::jsonable {
        struct cardExtendedSerialNumber {
          ddd::structure::general::iObj serialNumber;
          ddd::structure::general::sObj monthYear;
          ddd::structure::general::iObj type;
          ddd::structure::general::iObj manufacturerCode;
        };

        cardExtendedSerialNumber      extendedSerialNumber;
        ddd::structure::general::hObj clockStop;
        ddd::structure::general::sObj cardApprovalNumber;
        ddd::structure::general::iObj cardPersonalID;
        ddd::structure::general::sObj embedderIcAssemblerID;
        ddd::structure::general::hObj icIdentifier;
        auto toJson() const -> nlohmann::json;
      };

      struct IC : public ddd::structure::general::jsonable {
        ddd::structure::general::hObj serialNumber;
        ddd::structure::general::hObj manufacturingReferences;
        auto toJson() const -> nlohmann::json;
      };

      struct APP_IDENTIFICATION : public ddd::structure::general::jsonable {
        ddd::structure::general::iObj typeOfTachographCardId;
        ddd::structure::general::hObj cardStructureVersion;
        ddd::structure::general::iObj noOfEventsPerType;
        ddd::structure::general::iObj noOfFaultsPerType;
        ddd::structure::general::iObj activityStructureLength;
        ddd::structure::general::iObj noOfCardVehicleRecords;
        ddd::structure::general::iObj noOfCardPlaceRecords;
        auto toJson() const -> nlohmann::json;
      };

      struct IDENTIFICATION : public ddd::structure::general::jsonable {
        ddd::structure::general::iObj issuingMemberState;
        ddd::structure::general::sObj number;
        ddd::structure::general::sObj issuingAuthorityName;
        ddd::structure::general::iObj issueDate;
        ddd::structure::general::iObj validityBegin;
        ddd::structure::general::iObj expiryDate;
        ddd::structure::general::sObj holderSurname;
        ddd::structure::general::sObj holderFirstNames;
        ddd::structure::general::sObj holderBirthDate;
        ddd::structure::general::sObj holderPreferredLanguage;
        auto toJson() const -> nlohmann::json;
      };

      struct EVENTS : public ddd::structure::general::jsonable {
        struct record {
          ddd::structure::general::iObj type;
          ddd::structure::general::iObj beginTime;
          ddd::structure::general::iObj endTime;
          ddd::structure::general::iObj vehicleRegistrationNation;
          ddd::structure::general::sObj vehicleRegistrationNumber;
        };

        std::vector<record> records;
        auto toJson() const -> nlohmann::json;
      };

      struct FAULTS : public ddd::structure::general::jsonable {
        struct record {
          ddd::structure::general::iObj type;
          ddd::structure::general::iObj beginTime;
          ddd::structure::general::iObj endTime;
          ddd::structure::general::iObj vehicleRegistrationNation;
          ddd::structure::general::sObj vehicleRegistrationNumber;
        };

        std::vector<record> records;
        auto toJson() const -> nlohmann::json;
      };

      struct DRIVER_ACTIVITY : public ddd::structure::general::jsonable {
        struct daily {
          struct change {
            ddd::structure::general::rObj raw;
            ddd::structure::general::iObj slot;
            ddd::structure::general::iObj crew;
            ddd::structure::general::iObj placed;
            ddd::structure::general::iObj activity;
            ddd::structure::general::iObj time;
          };

          ddd::structure::general::iObj previousRecordLength;
          ddd::structure::general::iObj recordDate;
          ddd::structure::general::iObj dailyPresenceCounter;
          ddd::structure::general::iObj dayDistance;
          std::vector<change>           changes;
        };

        ddd::structure::general::iObj POR;
        ddd::structure::general::iObj PNR;
        std::vector<daily> dailyChange;
        auto toJson() const -> nlohmann::json;
      };

      struct VEHICLES_USED : public ddd::structure::general::jsonable {
        struct record {
          ddd::structure::general::iObj odometerBegin;
          ddd::structure::general::iObj odometerEnd;
          ddd::structure::general::iObj firstUse;
          ddd::structure::general::iObj lastUse;
          ddd::structure::general::iObj registrationNation;
          ddd::structure::general::sObj registrationNumber;
          ddd::structure::general::iObj vuDataBlockCounter;
        };

        ddd::structure::general::iObj PNR;
        std::vector<record> records;
        auto toJson() const -> nlohmann::json;
      };

      struct PLACES : public ddd::structure::general::jsonable {
        struct record {
          ddd::structure::general::iObj entryTime;
          ddd::structure::general::iObj entryTypeDailyWorkPeriod;
          ddd::structure::general::iObj dailyWorkPeriodCountry;
          ddd::structure::general::iObj dailyWorkPeriodRegion;
          ddd::structure::general::iObj vehicleOdometerValue;
        };

        ddd::structure::general::iObj PNR;
        std::vector<record>           records;
        auto toJson() const -> nlohmann::json;
      };

      struct CONTROL_ACTIVITY : public ddd::structure::general::jsonable {
        ddd::structure::general::iObj type;
        ddd::structure::general::iObj time;
        ddd::structure::general::iObj cardType;
        ddd::structure::general::iObj cardIssuingMemberState;
        ddd::structure::general::sObj cardNumber;
        ddd::structure::general::iObj vehicleRegistrationNation;
        ddd::structure::general::sObj vehicleRegistrationNumber;
        ddd::structure::general::iObj downloadPeriodBegin;
        ddd::structure::general::iObj downloadPeriodEnd;
        auto toJson() const -> nlohmann::json;
      };

      struct SPECIFIC_CONDITIONS : public ddd::structure::general::jsonable {
        struct record {
          ddd::structure::general::iObj entryTime;
          ddd::structure::general::iObj type;
        };

        std::vector<record> records;
        auto toJson() const -> nlohmann::json;
      };

      struct CARD_CERT {};
      struct CA_CERT {};
    }
  }
}
