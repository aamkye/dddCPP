#pragma once

#include <iostream>
#include <json.hpp>
#include <vector>

using bVec = std::vector<unsigned char>;

namespace ddd {
  namespace identificator {
    namespace common {
      static const uint32_t END = 0x0;
    }
    namespace card {
      static const uint32_t DRIVER = 0x0;
      static const uint32_t TRUCK = 0x1;
    }

    namespace data {
      namespace type {
        static const uint32_t DATA = 0x0;
        static const uint32_t CERT = 0x1;
      }
    }

    namespace ef {
      static const uint32_t ICC                  = 0x0002;
      static const uint32_t IC                   = 0x0005;
      static const uint32_t APP_IDENTIFICATION   = 0x0501;
      static const uint32_t IDENTIFICATION       = 0x0520;
      static const uint32_t DRIVING_LICENCE_INFO = 0x0521;
      static const uint32_t EVENTS               = 0x0502;
      static const uint32_t FAULTS               = 0x0503;
      static const uint32_t DRIVER_ACTIVITY      = 0x0504;
      static const uint32_t VEHICLES_USED        = 0x0505;
      static const uint32_t PLACES               = 0x0506;
      static const uint32_t CURRENT_USAGE        = 0x0507;
      static const uint32_t CONTROL_ACTIVITY     = 0x0508;
      static const uint32_t CARD_DOWNLOAD        = 0x050E;
      static const uint32_t SPECIFIC_CONDITIONS  = 0x0522;
      static const uint32_t CARD_CERT            = 0xC100;
      static const uint32_t CA_CERT              = 0xC108;
    }

    namespace ed {
      static const uint32_t OVERVIEW          = 0x7601;
      static const uint32_t ACTIVITIES        = 0x7602;
      static const uint32_t EVENTS_AND_FAULTS = 0x7603;
      static const uint32_t DETAILED_SPEED    = 0x7604;
      static const uint32_t TECHNICAL_DATA    = 0x7605;
    }
  }

  namespace structure {
    namespace general {
      struct rObj {
        bVec raw;
        bVec data;
      };

      struct sObj : public rObj {
        std::string data;
      };

      struct hObj : public rObj {
        std::string data;
      };

      struct iObj : public rObj {
        uint32_t data;
      };

      struct dataObj : public rObj {
        ddd::structure::general::iObj id;
        ddd::structure::general::iObj length;
        ddd::structure::general::iObj type;
      };

      struct jsonable {
        virtual auto toJson() const -> nlohmann::json = 0;
      };
    }
  }
}
