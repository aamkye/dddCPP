/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#include <card/Interface.hpp>

ddd::Interface::Interface() {}
ddd::Interface::~Interface() {}

auto ddd::Interface::toJson(const std::string&, const bool&) const -> bool {
  return true;
}
