#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

void fill_rand(std::vector<int> v)
{
    for(auto & a: v)
        a = rand() % (2 * v.size());
}

int main()
{
    std::vector<int> v(10);
    fill_rand(v);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
}
