#include <cstdint>
#include <initializer_list>

constexpr std::uint64_t from_bytes()
{
    return 0;
}

template<typename T, typename... Ts>
constexpr std::uint64_t from_bytes(T c, Ts... chars)
{
    
    return (std::uint64_t(c) << (sizeof...(chars) * 8)) + from_bytes(chars...);
}

const std::uint64_t ELF_MAGIC_NUMBER = from_bytes(0x7F, 'E', 'L', 'F', 'A', 'B');

int main()
{
    static_assert(ELF_MAGIC_NUMBER == 0x7F454c464142, "!");
}
