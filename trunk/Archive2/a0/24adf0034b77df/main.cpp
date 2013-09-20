#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
 
    auto lower = std::lower_bound(data.begin(), data.end(), 4);
    auto upper = std::upper_bound(data.begin(), data.end(), 4);
 
    std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
}