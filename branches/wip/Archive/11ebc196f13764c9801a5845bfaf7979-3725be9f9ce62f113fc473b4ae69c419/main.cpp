#include <iostream>
#include <vector>
#include <algorithm>  // for transform and min
#include <functional> // for std::plus
#include <iterator>   // for std::begin, but it's
                      // implicitly included by <vector>
int main()
{
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 5};
    auto size = std::min(a.size(), b.size());
    std::vector<int> c(size); // creates the third vector big enough for results

    std::transform(
        begin(a), begin(a)+size, begin(b),
        begin(c), std::plus<int>()
    );

    for (int i : c) std::cout << i << ' ';
}