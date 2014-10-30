#include <iostream>
#include <numeric>
#include <vector>

int main() {

    std::vector<double> v = { 0.5, 0.6, 0.7 };

    // gives wrong result due integer initial value
    std::cout << std::accumulate( v.begin(), v.end(), 0 ) << std::endl; // no warning


    return 0;
}