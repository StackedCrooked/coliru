#include <iostream>

int main()
{ 
    auto const * p = std::hex; //error by GCC
    auto * const q = std::hex; //ok 
}