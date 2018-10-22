#pragma once

#include <json.hpp>
#include <structure/General.hpp>

namespace ddd {
  namespace structure {
    namespace ed {
      struct OVERVIEW : public ddd::structure::general::jsonable {
        struct vuCompanyLocks {
          struct record {
            ddd::structure::general::iObj lockInTime;
            ddd::structure::general::iObj lockOutTime;
            ddd::structure::general::sObj companyName;
            ddd::structure::general::sObj companyAddress;
            ddd::structure::general::iObj cardType;
            ddd::structure::general::iObj cardIssuingMemberState;
            ddd::structure::general::sObj cardNumber;
          };

          ddd::structure::general::iObj noOfLocks;
          std::vector<record> records;
        };

        struct vuControlActivity {
          struct record {
            ddd::structure::general::iObj type;
            ddd::structure::general::iObj controlTime;
            ddd::structure::general::iObj cardType;
            ddd::structure::general::iObj cardIssuingMemberState;
            ddd::structure::general::sObj cardNumber;
            ddd::structure::general::iObj downloadPeriodBeginTime;
            ddd::structure::general::iObj downloadPeriodEndTime;
          };

          ddd::structure::general::iObj noOfControls;
          std::vector<record> records;
        };

        ddd::structure::general::rObj memberStateCertificate;
        ddd::structure::general::rObj VUCertificate;
        ddd::structure::general::sObj VIN;
        ddd::structure::general::iObj vehicleRegistrationNation;
        ddd::structure::general::sObj vehicleRegistrationNumber;
        ddd::structure::general::iObj currentDateTime;
        ddd::structure::general::iObj minDownloadableTime;
        ddd::structure::general::iObj maxDownloadableTime;
        ddd::structure::general::iObj cardSlotsStatus;
        ddd::structure::general::iObj downloadingTime;
        ddd::structure::general::iObj cardType;
        ddd::structure::general::iObj cardIssuingMemberState;
        ddd::structure::general::sObj cardNumber;
        ddd::structure::general::sObj companyOrWorkshopName;
        vuCompanyLocks vuCompanyLocks;
        vuControlActivity vuControlActivity;
        ddd::structure::general::rObj signature;
        auto toJson() const -> nlohmann::json;
      };

      struct ACTIVITIES : public ddd::structure::general::jsonable {
        struct vuCardIW {
          struct record {
            ddd::structure::general::sObj holderSurname;
            ddd::structure::general::sObj holderFirstNames;
            ddd::structure::general::iObj cardType;
            ddd::structure::general::iObj cardIssuingMemberState;
            ddd::structure::general::sObj cardNumber;
            ddd::structure::general::iObj cardExpiryDate;
            ddd::structure::general::iObj cardInsertionTime;
            ddd::structure::general::iObj vehicleOdometerValueAtInsertion;
            ddd::structure::general::iObj cardSlotNumber;
            ddd::structure::general::iObj cardWithdrawalTime;
            ddd::structure::general::iObj vehicleOdometerValueAtWithdrawal;
            ddd::structure::general::iObj vehicleRegistrationNation;
            ddd::structure::general::sObj vehicleRegistrationNumber;
            ddd::structure::general::iObj previousCardWithdrawalTime;
            ddd::structure::general::iObj manualInputFlag;
          };

          ddd::structure::general::iObj noOfRecords;
          std::vector<record> records;
        };

        struct vuActivityDaily {
          struct change {
            ddd::structure::general::rObj raw;
            ddd::structure::general::iObj slot;
            ddd::structure::general::iObj crew;
            ddd::structure::general::iObj placed;
            ddd::structure::general::iObj activity;
            ddd::structure::general::iObj time;
          };

          ddd::structure::general::iObj noOfChanges;
          std::vector<change> changes;
        };

        struct vuPlaceDailyWorkPeriod {
          struct record {
            ddd::structure::general::iObj cardType;
            ddd::structure::general::iObj cardIssuingMemberState;
            ddd::structure::general::sObj cardNumber;
            ddd::structure::general::iObj entryTime;
            ddd::structure::general::iObj entryTypeDailyWorkPeriod;
            ddd::structure::general::iObj dailyWorkPeriodCountry;
            ddd::structure::general::iObj dailyWorkPeriodRegion;
            ddd::structure::general::iObj vehicleOdometerValue;
          };

          ddd::structure::general::iObj noOfRecords;
          std::vector<record> records;
        };

        struct vuSpecificCondition {
          struct record {
            ddd::structure::general::iObj entryTime;
            ddd::structure::general::iObj type;
          };

          ddd::structure::general::iObj noOfRecords;
          std::vector<record> records;
        };

        ddd::structure::general::iObj timeReal;
        ddd::structure::general::iObj odometerValueMidnight;
        vuCardIW vuCardIW;
        vuActivityDaily vuActivityDaily;
        vuPlaceDailyWorkPeriod vuPlaceDailyWorkPeriod;
        vuSpecificCondition vuSpecificCondition;
        ddd::structure::general::rObj signature;
        auto toJson() const -> nlohmann::json;
      };

      struct EVENTS_AND_FAULTS : public ddd::structure::general::jsonable {
        struct vuFault {
          struct fault {
            ddd::structure::general::iObj type;
            ddd::structure::general::iObj recordPurpose;
            ddd::structure::general::iObj beginTime;
            ddd::structure::general::iObj endTime;
            ddd::structure::general::iObj driverSlotBeginCardType;
            ddd::structure::general::iObj driverSlotBeginCardIssuingMemberState;
            ddd::structure::general::sObj driverSlotBeginCardNumber;
            ddd::structure::general::iObj coDriverSlotBeginCardType;
            ddd::structure::general::iObj coDriverSlotBeginCardIssuingMemberState;
            ddd::structure::general::sObj coDriverSlotBeginCardNumber;
            ddd::structure::general::iObj driverSlotEndCardType;
            ddd::structure::general::iObj driverSlotEndCardIssuingMemberState;
            ddd::structure::general::sObj driverSlotEndCardNumber;
            ddd::structure::general::iObj coDriverSlotEndCardType;
            ddd::structure::general::iObj coDriverSlotEndCardIssuingMemberState;
            ddd::structure::general::sObj coDriverSlotEndCardNumber;
          };

          ddd::structure::general::iObj noOfFaults;
          std::vector<fault> faults;
        };

        struct vuEvent {
          struct event {
            ddd::structure::general::iObj type;
            ddd::structure::general::iObj recordPurpose;
            ddd::structure::general::iObj beginTime;
            ddd::structure::general::iObj endTime;
            ddd::structure::general::iObj driverSlotBeginCardType;
            ddd::structure::general::iObj driverSlotBeginCardIssuingMemberState;
            ddd::structure::general::sObj driverSlotBeginCardNumber;
            ddd::structure::general::iObj coDriverSlotBeginCardType;
            ddd::structure::general::iObj coDriverSlotBeginCardIssuingMemberState;
            ddd::structure::general::sObj coDriverSlotBeginCardNumber;
            ddd::structure::general::iObj driverSlotEndCardType;
            ddd::structure::general::iObj driverSlotEndCardIssuingMemberState;
            ddd::structure::general::sObj driverSlotEndCardNumber;
            ddd::structure::general::iObj coDriverSlotEndCardType;
            ddd::structure::general::iObj coDriverSlotEndCardIssuingMemberState;
            ddd::structure::general::sObj coDriverSlotEndCardNumber;
            ddd::structure::general::iObj similarEventsNumber;
          };

          ddd::structure::general::iObj noOfEvents;
          std::vector<event> events;
        };

        struct vuOverSpeedingEvent {
          struct event {
            ddd::structure::general::iObj type;
            ddd::structure::general::iObj recordPurpose;
            ddd::structure::general::iObj beginTime;
            ddd::structure::general::iObj endTime;
            ddd::structure::general::iObj maxSpeedValue;
            ddd::structure::general::iObj averageSpeedValue;
            ddd::structure::general::iObj driverSlotBeginCardType;
            ddd::structure::general::iObj driverSlotBeginCardIssuingMemberState;
            ddd::structure::general::sObj driverSlotBeginCardNumber;
            ddd::structure::general::iObj similarEventsNumber;
          };

          ddd::structure::general::iObj noOfEvents;
          std::vector<event> events;
        };

        struct vuTimeAdjustment {
          struct record {
            ddd::structure::general::iObj oldTimeValue;
            ddd::structure::general::iObj newTimeValue;
            ddd::structure::general::sObj workshopName;
            ddd::structure::general::sObj workshopAddress;
            ddd::structure::general::iObj workshopCardType;
            ddd::structure::general::iObj workshopCardIssuingMemberState;
            ddd::structure::general::sObj workshopCardNumber;
          };

          ddd::structure::general::iObj noOfRecords;
          std::vector<record> records;
        };

        vuFault vuFault;
        vuEvent vuEvent;
        ddd::structure::general::iObj lastOverspeedControlTime;
        ddd::structure::general::iObj firstOverspeedSince;
        ddd::structure::general::iObj numberOfOverspeedSince;
        vuOverSpeedingEvent vuOverSpeedingEvent;
        vuTimeAdjustment vuTimeAdjustment;
        ddd::structure::general::rObj signature;
        auto toJson() const -> nlohmann::json;
      };

      struct DETAILED_SPEED : public ddd::structure::general::jsonable {
        struct vuDetailedSpeed {
          struct speedBlock {
            struct record {
              ddd::structure::general::iObj speed;
            };

            ddd::structure::general::iObj speedBlockBeginDate;
            std::vector<record> records;
          };

          ddd::structure::general::iObj noOfSpeedBlocks;
          std::vector<speedBlock> speedBlocks;
        };

        vuDetailedSpeed vuDetailedSpeed;
        ddd::structure::general::rObj signature;
        auto toJson() const -> nlohmann::json;
      };

      struct TECHNICAL_DATA : public ddd::structure::general::jsonable {
        struct vuCalibration {
          struct record {
            ddd::structure::general::sObj calibrationPurpose;
            ddd::structure::general::sObj workshopName;
            ddd::structure::general::sObj workshopAddress;
            ddd::structure::general::iObj workshopCardType;
            ddd::structure::general::iObj workshopCardIssuingMemberState;
            ddd::structure::general::sObj workshopCardNumber;
            ddd::structure::general::iObj workshopCardExpiryDate;
            ddd::structure::general::sObj VIN;
            ddd::structure::general::iObj vehicleRegistrationNation;
            ddd::structure::general::sObj vehicleRegistrationNumber;
            ddd::structure::general::iObj wVehicleCharacteristicConstant;
            ddd::structure::general::iObj kConstantOfRecordingEquipment;
            ddd::structure::general::iObj lTyreCircumference;
            ddd::structure::general::sObj tyreSize;
            ddd::structure::general::iObj authorisedSpeed;
            ddd::structure::general::iObj oldOdometerValue;
            ddd::structure::general::iObj newOdometerValue;
            ddd::structure::general::iObj oldTimeValue;
            ddd::structure::general::iObj newTimeValue;
            ddd::structure::general::iObj nextCalibrationDate;
          };

          ddd::structure::general::iObj noOfRecords;
          std::vector<record> records;
        };

        struct vuSerialNumber {
          ddd::structure::general::iObj serialNumber;
          ddd::structure::general::sObj monthYear;
          ddd::structure::general::iObj type;
          ddd::structure::general::iObj manufacturerCode;
        };

        struct sensorSerialNumber {
          ddd::structure::general::iObj serialNumber;
          ddd::structure::general::sObj monthYear;
          ddd::structure::general::iObj type;
          ddd::structure::general::iObj manufacturerCode;
        };

        ddd::structure::general::sObj vuManufacturerName;
        ddd::structure::general::sObj vuManufacturerAddress;
        ddd::structure::general::sObj vuPartNumber;
        ddd::structure::general::sObj vuSoftwareVersion;
        ddd::structure::general::iObj vuSoftInstallationDate;
        ddd::structure::general::iObj vuManufacturingDate;
        ddd::structure::general::sObj vuApprovalNumber;
        ddd::structure::general::sObj sensorApprovalNumber;
        ddd::structure::general::iObj sensorPairingDateFirst;
        sensorSerialNumber sensorSerialNumber;
        vuSerialNumber vuSerialNumber;
        vuCalibration vuCalibration;
        ddd::structure::general::rObj signature;
        auto toJson() const -> nlohmann::json;
      };
    }
  }
}
