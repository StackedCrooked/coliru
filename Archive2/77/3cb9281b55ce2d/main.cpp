#include <algorithm>
#include <iostream>
#include <cstdlib>
 
int main()
{
    std::vector<int> v(5);
    std::generate(v.begin(), v.end(), std::rand); // Using the C function rand()
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
 
    // initalize with default values 0,1,2,3,4 / use of a lambda function
    int n(0);
    std::generate(v.begin(), v.end(), [&](){ return n++; }); 
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
}