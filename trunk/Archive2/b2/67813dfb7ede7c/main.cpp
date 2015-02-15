#include <iostream>
#include <utility>

int main()
{
    int a[4][3] = {1,2,3,4,5,6,7,8,9,10,11,12};

    std::cout << "Before swap: \n";
    for(auto& r: a) {
        for(int x : r) std::cout << x << ' ';
        std::cout << '\n';
    }

    std::swap(a[0], a[3]);
    
    std::cout << "After swap: \n";
    for(auto& r: a) {
        for(int x : r) std::cout << x << ' ';
        std::cout << '\n';
    }
}
