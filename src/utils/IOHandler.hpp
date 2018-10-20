#pragma once

#include <structure/General.hpp>
#include <fstream>
#include <iostream>
#include <vector>

namespace ddd {
  class IOHandler {
  public:
    IOHandler();
    IOHandler(const std::string& name);
    auto close() -> void;
    auto setFileLength() -> void;
    auto moveToBeg() -> void;
    auto readBin(const uint32_t& size) -> bVec;
    auto removeExtension(const std::string& filename) const -> std::string;

    uint32_t    totalRead  = 0;
    uint32_t    fileLength = 0;
    std::string fileName   = "";

  private:
    std::ifstream fileHandler;
  };
}
