/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 */

#include <fstream>
#include <streambuf>
#include <iostream>
#include <string>
#include <ctime>
#include <utils/Limiter.hpp>
#include <utils/Config.hpp>

ddd::Limiter::Limiter() {
  if(!this->check()){
    exit(-1);
  }
}

bool ddd::Limiter::check(){
  bool check = false;
  for(auto const& x : ddd::Config::macAdresses){
    if(this->getMac(x.name) == x.value){
      check = true;
      break;
    }
  }

  check &= (this->getTime() < ddd::Config::expireDate);

  return check;
}

std::string ddd::Limiter::getMac(const std::string &ifname) {
  std::ifstream iface("/sys/class/net/"+ifname+"/address");
  std::string str((std::istreambuf_iterator<char>(iface)), std::istreambuf_iterator<char>());
  str.erase(str.find_last_not_of('\n')+1);
  return str;
}

uint32_t ddd::Limiter::getTime() {
  time_t t = std::time(0);
  uint32_t now = static_cast<uint32_t> (t);
  return now;
}
