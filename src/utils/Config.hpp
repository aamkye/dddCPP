#include <vector>
#include <string>

namespace ddd {
  namespace Config {
    struct macAdress {
      std::string name;
      std::string value;
    };

    std::vector<macAdress> macAdresses = {
      {"en0", "c4:b3:01:bb:c6:fb"}, // MACBOOK
      {"p2p0", "06:b3:01:bb:c6:fb"},
      {"eth0", "02:50:00:00:00:01"}, // DOCKER
      {"docker0", "02:42:a8:d5:04:2e"},
      {"enp0s25", "18:a9:05:f1:f0:37"}}; // TARGET @ CANDYSHOP

    uint32_t expireDate = 1630316800; // 30.06.2018 00:00
  }
}
