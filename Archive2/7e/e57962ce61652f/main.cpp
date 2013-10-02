#include <iostream>

int main()
{ 
    auto const * p = std::hex; //ok by Clang
    auto * const q = std::hex; //ok 
}