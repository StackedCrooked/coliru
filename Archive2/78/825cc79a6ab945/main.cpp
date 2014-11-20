#include <cstddef>

template <size_t N>
constexpr size_t pow = 2 * pow<N - 1>;

template <>
constexpr size_t pow<0> = 1;

int main()
{
    static_assert(pow<4> == 16, "!");
}
