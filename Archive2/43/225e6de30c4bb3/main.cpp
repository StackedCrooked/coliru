#include <iostream>
#include <array>

struct WithAnArray {
    int taba[3];
    int tabb[3] { 4, 5, 6 };
    
    std::array<int,3> arraya;
    std::array<int,3> arrayb { { 4, 5, 6 } };
    
    WithAnArray() :
      taba { 1, 2, 3 },      
      arraya { { 1, 2, 3 } } {
    }
};

int main()
{
    WithAnArray fool;
    for ( auto v : fool.taba ) std::cout << v << " ";
    for ( auto v : fool.tabb ) std::cout << v << " ";
    std::cout << std::endl;
    for ( auto v : fool.arraya ) std::cout << v << " ";
    for ( auto v : fool.arrayb ) std::cout << v << " ";
     std::cout << std::endl;
   
}
