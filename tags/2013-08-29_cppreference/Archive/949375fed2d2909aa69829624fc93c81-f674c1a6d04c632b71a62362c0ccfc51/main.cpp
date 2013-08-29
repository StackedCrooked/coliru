#include <type_traits>
#include <vector>

#ifdef MSVC_VER
#define ValueType(T) typename T::value_type
#else
template<typename T>
using ValueType = typename T::value_type;
#endif

#ifdef MSVC_VER
#define LEFT_ (
#define RIGHT_ )
#else
#define LEFT_ <
#define RIGHT_ >
#endif

#include <iostream>

int main() {
    ValueType LEFT_ std::vector<int> RIGHT_ x = 100; // lolol
    std::cout << x;
}



