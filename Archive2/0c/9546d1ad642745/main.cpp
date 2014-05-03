#include <cstdint>

struct version
{
  static constexpr std::uint8_t major = 0;
  static constexpr std::uint8_t minor = 0;
  static constexpr std::uint8_t bugfix = 0;
};

constexpr auto& version_string()
{
  static constexpr const char vstring[] = {version::major+'0', '.', version::minor+'0', '.', version::bugfix+'0'};
  return vstring;
}

int main(){}