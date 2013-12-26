#include <iostream>
#include <memory>
 
int main() 
{
    std::unique_ptr<int> p1(new int(42));
    std::unique_ptr<int> p2(new int(42));
 
    std::cout << "p1 == p1: " << (p1 == p1) << '\n';
 
    // p1 and p2 point to different memory locations, so p1 != p2
    std::cout << "p1 == p2: " << (p1 == p2) << '\n';
}