#include <cstdlib>
#include <type_traits>
#include <iostream>

template<bool is32>
struct S;

template<>
struct S<true> {
    typedef std::int32_t type;
};

template<>
struct S<false> {
    typedef std::int64_t type;  
};

typedef S<sizeof(char) == 4>::type myint;

int main() {
    std::cout << sizeof(char) << '\n' << sizeof(myint);
}