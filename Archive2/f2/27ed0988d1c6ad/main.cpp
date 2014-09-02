#include <iostream>
#include <utility>

struct A
{
  uint16_t a;
  uint16_t b;
};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    int a = 0x12345678;
    std::cout << sizeof(int) << "..." << sizeof(uint16_t) << std::endl;
    A p{a,a}; // !!!! no warning or error on conversion !!!!
    std::cout << p.a << ":" << p.b << std::endl;
    uint16_t b = a; // !!!! correct behavior: -Wconversion triggers warning, which -Werror turns to an error
    std::cout << b << std::endl;
    return 0;
}