#include <cstdint>

template < std::intptr_t Reg >
struct peripheral {};

int main()
{
    std::uint32_t reg;
    peripheral< __builtin_constant_p(reinterpret_cast< std::intptr_t >( &reg )) > mocked;
}