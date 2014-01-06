#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>

int main() {
    std::array<int, 2> x {1, 2};
    std::array<int, 2> y(x);
    y[1] = 3;
    
    std::cout << y[1] << x[1];
    
    int a[2] {1, 2};
    int b[2] = a;
}