#include <card/Raw.hpp>
#include <card/Driver.hpp>
#include <card/Truck.hpp>
#include <card/Interface.hpp>
#include <structure/Truck.hpp>
#include <structure/Driver.hpp>
#include <iostream>
#include <map>
#include <vector>

ddd::Raw::Raw() {}

ddd::Raw::Raw(std::string name)
  : ioHandler(name), convertTool(), chroma() {
  proceed();

  std::unique_ptr<ddd::Interface> obj;

  switch(this->cardType) {
    case ddd::identificator::card::DRIVER: {
      obj = std::make_unique<ddd::Driver>(this->data);
    } break;
    case ddd::identificator::card::TRUCK: {
      obj = std::make_unique<ddd::Truck>(this->vectorData);
    } break;
    default: {
      std::cout << chroma("Unknown file type", {chroma::foreground::iRed, chroma::type::bold}) << std::endl;
      exit(-1);
    } break;
  }
  obj->toJson(ioHandler.removeExtension(ioHandler.fileName) + ".json", true);
}

ddd::Raw::~Raw() {
  ioHandler.close();
}

bool ddd::Raw::proceed() {
  bool end = false;
  do {
    bVec rawId = ioHandler.readBin(2);
    uint32_t id = convertTool.bitShift(rawId);

    // std::cout << "Structure read (dec): " << chroma(id, {chroma::foreground::iGreen, chroma::type::bold}) << std::endl;

    switch (id) {
      case ddd::identificator::ef::ICC:
      case ddd::identificator::ef::IC:
      case ddd::identificator::ef::APP_IDENTIFICATION:
      case ddd::identificator::ef::IDENTIFICATION:
      case ddd::identificator::ef::DRIVING_LICENCE_INFO:
      case ddd::identificator::ef::EVENTS:
      case ddd::identificator::ef::FAULTS:
      case ddd::identificator::ef::DRIVER_ACTIVITY:
      case ddd::identificator::ef::VEHICLES_USED:
      case ddd::identificator::ef::PLACES:
      case ddd::identificator::ef::CURRENT_USAGE:
      case ddd::identificator::ef::CONTROL_ACTIVITY:
      case ddd::identificator::ef::CARD_DOWNLOAD:
      case ddd::identificator::ef::SPECIFIC_CONDITIONS:
      case ddd::identificator::ef::CARD_CERT:
      case ddd::identificator::ef::CA_CERT: {
        readDriverStructure(rawId);
        this->cardType = ddd::identificator::card::DRIVER;
      } break;

      case ddd::identificator::ed::OVERVIEW:
      case ddd::identificator::ed::ACTIVITIES:
      case ddd::identificator::ed::EVENTS_AND_FAULTS:
      case ddd::identificator::ed::DETAILED_SPEED:
      case ddd::identificator::ed::TECHNICAL_DATA: {
        readTruckStructure(rawId);
        this->cardType = ddd::identificator::card::TRUCK;
      } break;

      case ddd::identificator::common::END: {
        end = true;
      } break;

      default: {
        std::cout << "Unknown structure read id (dec): " << chroma(id, {chroma::foreground::iRed, chroma::type::bold}) << std::endl;
        exit(-1);
      }
    }
  } while (!end);
  return true;
}

bool ddd::Raw::readDriverStructure(const bVec &rawId) {
  ddd::structure::general::dataObj obj;

  obj.id.raw = rawId;
  obj.type.raw = ioHandler.readBin(1);
  obj.length.raw = ioHandler.readBin(2);

  convertTool.parse(obj.id);
  convertTool.parse(obj.type);
  convertTool.parse(obj.length);

  obj.raw = ioHandler.readBin(obj.length.data);

  if (obj.type.data == ddd::identificator::data::type::DATA) {
    // std::cout << "Driver data type (dec): " << chroma(obj.type.data,f{chroma::Foreground::iGreen,tchroma::Type::bold}) << std::endl;
    data[obj.id.data] = obj;
  } else if (obj.type.data == ddd::identificator::data::type::CERT) {
    // std::cout << "Driver cert type (dec): " << chroma(obj.type.data,f{chroma::Foreground::iGreen,tchroma::Type::bold}) << std::endl;
    certData[obj.id.data] = obj;
  } else {
    std::cout << "Unknown driver type (dec): " << chroma(obj.type.data, {chroma::foreground::iRed, chroma::type::bold}) << std::endl;
    exit(-1);
  }

  ioHandler.totalRead += 5 + obj.length.data;
  return true;
}

bool ddd::Raw::readTruckStructure(const bVec &rawId) {
  auto append = [this](bVec& a, const uint32_t & contentSize) {
    bVec readBuffer = ioHandler.readBin(contentSize);
    a.insert(a.end(), readBuffer.begin(), readBuffer.end());
  };

  auto appendLoop = [this](bVec& a, const uint32_t& loopSize, const uint32_t& contentSize){
    ddd::structure::general::iObj temp;

    temp.raw = ioHandler.readBin(loopSize);
    a.insert(a.end(), temp.raw.begin(), temp.raw.end());
    convertTool.parse(temp);
    for (uint32_t i = 0; i < temp.data; ++i) {
      bVec readBuffer = ioHandler.readBin(contentSize);
      a.insert(a.end(), readBuffer.begin(), readBuffer.end());
    }
  };

  ddd::structure::general::dataObj obj;
  ddd::structure::general::iObj temp;

  obj.id.raw = rawId;
  convertTool.parse(obj.id);
  obj.type.data = ddd::identificator::data::type::DATA;

  uint32_t diff = ioHandler.totalRead;

  // std::cout << "Truck data type (dec): " << chroma(obj.id.data,f{chroma::Foreground::iGreen,tchroma::Type::bold}) << std::endl;

  switch (obj.id.data) {
    case ddd::identificator::ed::OVERVIEW: {
      append(obj.raw, 491);
      appendLoop(obj.raw, 1, 98);
      appendLoop(obj.raw, 1, 31);
      append(obj.raw, 128);
    } break;
    case ddd::identificator::ed::ACTIVITIES: {
      append(obj.raw, 7);
      appendLoop(obj.raw, 2, 129);
      appendLoop(obj.raw, 2, 2);
      appendLoop(obj.raw, 1, 28);
      appendLoop(obj.raw, 2, 5);
      append(obj.raw, 128);
    } break;
    case ddd::identificator::ed::EVENTS_AND_FAULTS: {
      appendLoop(obj.raw, 1, 82);
      appendLoop(obj.raw, 1, 83);
      append(obj.raw, 9);
      appendLoop(obj.raw, 1, 31);
      appendLoop(obj.raw, 1, 98);
      append(obj.raw, 128);
    } break;
    case ddd::identificator::ed::DETAILED_SPEED: {
      appendLoop(obj.raw, 2, 64);
      append(obj.raw, 128);
    } break;
    case ddd::identificator::ed::TECHNICAL_DATA: {
      append(obj.raw, 136);
      appendLoop(obj.raw, 1, 167);
      append(obj.raw, 128);
    } break;

    default: {
        std::cout << "Unknown truck type (dec): " << chroma(obj.type.data, {chroma::foreground::iGreen, chroma::type::bold}) << std::endl;
    }
  }

  obj.length.data = 2 + (ioHandler.totalRead - diff);
  vectorData[obj.id.data].push_back(obj);

  return true;
}
