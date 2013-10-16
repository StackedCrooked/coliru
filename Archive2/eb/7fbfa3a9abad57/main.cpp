#include <iostream>
#include <boost/math/distributions/exponential.hpp>

using namespace boost::math;

int main() 
{
    auto const lambda = 1.0;
    auto d = exponential_distribution<>{lambda};
    std::cout << pdf(d, 0) << "\n"; // exp(0) = 1
    std::cout << pdf(d, 1) << "\n"; // exp(-1) = 0.367879
}
