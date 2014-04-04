#include <iostream>
#include <limits>

int main()
{
    enum { first=0x01, second=first << 1, third=second << 1, LAST_NOT_USED=third << 1 };

    static const std::uint8_t l_allFlags((std::numeric_limits<std::uint8_t>::max() - LAST_NOT_USED + 1u) ^ std::numeric_limits<std::uint8_t>::max());

    std::cout << "all flags: 0x" << std::hex << +l_allFlags;
}