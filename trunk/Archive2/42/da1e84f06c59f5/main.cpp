#include <iostream>
#include <ios>
#include <vector>

int main()
{
    std::cout.precision(12);
    std::vector<double> data{ 234343.0, 3.41e10, 19.999999999, -10.1, -0.0000001 };
    for(auto n : data) std::cout << n << " -> " << (long long)(n) << std::endl;
    return 0;
}