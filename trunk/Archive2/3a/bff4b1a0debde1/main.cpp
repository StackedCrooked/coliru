#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    using std::begin;
    using std::end;
    
    std::vector<double> vars = {1, 2, 3};
    
    auto multi = std::accumulate(begin(vars), end(vars), 1, std::multiplies<double>());
    std::cout << multi;
}