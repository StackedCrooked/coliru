#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


int main()
{
    std::vector<int> v { 1,2,3,4 };
    copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
}

