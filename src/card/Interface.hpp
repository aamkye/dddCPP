/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#pragma once

#include <string>

namespace ddd {
  class Interface {
   public:
    Interface();
    virtual ~Interface();
    virtual auto toJson(const std::string&, const bool&) const -> bool;
  };
}
