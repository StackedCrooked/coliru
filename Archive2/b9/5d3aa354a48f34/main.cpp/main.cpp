#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <limits>
 
int main()
{
    // construction uses aggregate initialization
    auto nan = std::numeric_limits<double>::signaling_NaN();
    std::array<std::array<double, 3>, 3> a1{ {nan} };  // double-braces required
}