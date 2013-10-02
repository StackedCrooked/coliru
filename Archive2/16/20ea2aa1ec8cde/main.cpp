#include <iostream>

int main()
{ 
    auto const * p = std::hex; //error
    auto * const q = std::hex; //ok
}