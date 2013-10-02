#include <iostream>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <vector>
 
int main() 
{
    const std::size_t items = 10;
 
    std::vector<int> v1, v2, dst;
 
    // fill the vectors
    for (std::size_t idx = 0; idx < items; ++idx) {
        v1.push_back(std::rand()%items);
        v2.push_back(std::rand()%items);
    }
 
    // sort
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
 
    // output v1
    std::cout << "v1 : ";
    std::copy(v1.begin(), v1.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    // output v2
    std::cout << "v2 : ";
    std::copy(v2.begin(), v2.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    // merge
    std::merge(v1.begin(), v1.end(),
               v2.begin(), v2.end(),
               std::back_inserter(dst));
 
    // output
    std::cout << "dst: ";
    std::copy(dst.begin(), dst.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}