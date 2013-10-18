#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

int main()
{
    auto ori = std::vector<double> { 0.1, -1.2, 2.4, 3.4, -7.1 };
    std::vector<double> out;

    std::copy_if(begin(ori), end(ori), std::back_inserter(out), [&](double d) { return d < 0.0; });
    std::copy(begin(out), end(out), std::ostream_iterator<double>(std::cout, ","));
}
