#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <array>
#include <algorithm>

int main() {
    std::array<int, 5> x = {2,3,1,4,5};
    std::array<int, 5> y = {1,3,5,7,9};
    std::array<int, 5> z = {3,5,4,6,1};
    std::array<int, 15> w;
    for (int i = 0; i < 5; i++) {
        w[i*3] = x[i];
        w[i*3+1] = y[i];
        w[i*3+2] = z[i];
    } 
    for (int i : w) std::cout << i;
}