#include <cstdint>

constexpr std::uint32_t from_bytes(char b1, char b2, char b3, char b4)
{
    return b4 + 
        (static_cast<std::uint32_t>(b3) << 8) + 
        (static_cast<std::uint32_t>(b2) << 16) + 
        (static_cast<std::uint32_t>(b1) << 24);
}

const std::uint32_t ELF_MAGIC_NUMBER = from_bytes( 0x7F, 'E', 'L', 'F' );

int main()
{
    static_assert(ELF_MAGIC_NUMBER == 0x7F454c46, "!");
}
