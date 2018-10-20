#include <utils/IOHandler.hpp>
#include <structure/General.hpp>
#include <fstream>
#include <iostream>
#include <vector>

ddd::IOHandler::IOHandler() {}

ddd::IOHandler::IOHandler(const std::string& name) {
  fileName = name;
  fileHandler.open(fileName.c_str(), std::ios::in | std::ifstream::binary);
  setFileLength();
}

auto ddd::IOHandler::close() -> void {
  fileHandler.close();
}

auto ddd::IOHandler::setFileLength() -> void {
  fileHandler.seekg(0, fileHandler.end);
  fileLength = fileHandler.tellg();
  fileHandler.seekg(0, fileHandler.beg);
}

auto ddd::IOHandler::moveToBeg() -> void {
  fileHandler.seekg(0, fileHandler.beg);
}

auto ddd::IOHandler::readBin(const uint32_t& size) -> bVec {
  std::vector<uint8_t> binary;
  binary.reserve(size);
  binary.insert(binary.begin(), size, 0);
  fileHandler.read((char*)&binary[0], size);
  totalRead += size;
  return binary;
}

auto ddd::IOHandler::removeExtension(const std::string& filename) const -> std::string {
  size_t lastdot = filename.find_last_of(".");
  if(lastdot == std::string::npos) return filename;
  return filename.substr(0, lastdot);
}
