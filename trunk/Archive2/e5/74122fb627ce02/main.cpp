#include <tuple>
#include <cstdint>
#include <iostream>

int main()
{
    struct empty {};
    std::tuple<std::int32_t, int, int> x;
    std::cout << sizeof(x) << " : " << &std::get<0>(x) << ", " << &std::get<1>(x) << ", " << &std::get<2>(x) << "\n";
}