#include <array>

using my_array = std::array<int, 11>;

template<size_t N>
struct S{};

constexpr auto f(my_array arg)
{
    return S<arg.size()>{};
}

int main()
{
    constexpr my_array a{};
    auto v1 = f(a);
    
    //bool check_the_type = v; // error: no viable conversion from 'S<11>' to 'bool'
}
