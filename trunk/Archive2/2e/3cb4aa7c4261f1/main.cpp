#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    double const a[] = { 0,1,2,3,4,5,6,7,8,9 };

    std::transform(std::begin(a), std::end(a), 
            std::ostream_iterator<double>(std::cout, " "),
            [](double x) { return x*1.7; });
}
