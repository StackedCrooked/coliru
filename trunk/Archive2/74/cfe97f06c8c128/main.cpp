#include <array>

struct litmus final : std::array<unsigned char, 16>
{
};
static_assert(std::is_pod<std::array<unsigned char, 16> >::value, "not pod");
static_assert(std::is_pod<litmus>::value, "not pod");
