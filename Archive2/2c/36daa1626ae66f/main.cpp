#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    const int N1 = 10;    // This can vary
    const int offset = 3; // This also can vary
    std::vector<int> chans(10);
    std::generate(chans.begin(), chans.end(), [=, count = 0]() mutable { return offset + N1 * count++; });
    std::copy(chans.begin(), chans.end(), std::ostream_iterator<int>(std::cout, " "));
}
