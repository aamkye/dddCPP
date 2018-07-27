/**
 * Amadeusz Kryze (c) 2016-2017
 * Robert Kujawski (c) 2016-2017
 *
 * ToonGet.com
 */

#include <card/Raw.hpp>
#include <utils/Limiter.hpp>
#include <string>
#include <vector>

auto main(int argc, char* argv[]) -> int {
  ddd::Limiter limiter;
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " '/path/file.ddd'" << std::endl;
    return 1;
  }

  ddd::Raw obj(argv[1]);
  return 0;
}
