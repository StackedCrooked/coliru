// g++ sizeofint.cpp --std=c++11 -Wconversion -Wall -Wextra -Werror -pedantic-errors
#include <iostream>
#include <utility>
#include <type_traits>

struct alignas(16) struct1 {
    short x, y, z;
};

struct struct2 {
    short a;
    struct1 s;
};

struct vec
{
    union {
       struct2 s1;
    short elements[3];
    };
};

static_assert(std::is_standard_layout<vec>::value, "not standard layout");
static_assert(std::is_pod<vec>::value, "not POD");

int main() {
    vec v;
    v.elements[0] = 123;
    v.elements[1] = 456;
    v.elements[2] = 789;
    // v.s1.a == 456 but v.s1.s.x != 456
    std::cout << v.s1.a << ' ' << v.s1.s.x << std::endl;
    return 0;
}