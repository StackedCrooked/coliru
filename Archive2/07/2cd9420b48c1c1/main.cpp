// from Scott Meyers' "Effective Modern C++"
#include <iostream>
#include <string>

template <typename T>
decltype(auto) ok(T i) {
    auto x = i + 1;
    return x;
}

template <typename T>
decltype(auto) undefined_behavior(T i) {
    auto x = i + 1;
    return (x);
}

int main()
{
    std::cout<<ok(41)<<std::endl;
    std::cout<<undefined_behavior(32)<<std::endl;
}
