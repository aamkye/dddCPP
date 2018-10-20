#include <card/Raw.hpp>
// #include <utils/Limiter.hpp>

auto main(int argc, char* argv[]) -> int {
  // ddd::Limiter limiter;
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " '/path/file.ddd'" << std::endl;
    return 1;
  }

  ddd::Raw obj(argv[1]);
  return 0;
}
