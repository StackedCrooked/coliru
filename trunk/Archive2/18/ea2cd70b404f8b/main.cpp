#include <iostream>
struct Empty {};
struct Bit {unsigned bit:1; };
int main()
{
    Empty e;
    Bit b;
    std::cout << "size of empty class: "     << sizeof e        << '\n'
              << "size of pointer : "        << sizeof &e       << '\n'
              << "size of array of 10 int: " << sizeof(int[10]) << '\n';
}