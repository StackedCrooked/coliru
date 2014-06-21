#include <cstdint>

struct chameleon
{
    template<typename T>
    constexpr operator T() const
    {
        return T{};
    }

    constexpr chameleon() = default;
};

template<std::size_t I>
struct placeholder : public chameleon
{
    using chameleon::chameleon;
};

int main()
{
    constexpr const placeholder<0> _1;

    return 0;
}
