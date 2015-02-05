#include <iostream>
#include <algorithm>
#include <limits>

int main()
{
    double nan = std::numeric_limits<double>::quiet_NaN();
    double arr[] = {1.0, nan, -1.0, nan, 2.0, nan, -2.0, nan};
    std::sort(std::begin(arr), std::end(arr));
    for(auto d: arr)
        std::cout << d << ' ';
}
