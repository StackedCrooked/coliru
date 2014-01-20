#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v(0);
    {
        int ints[] = { 1, 2, 3, 4, 5, 6 };
        std::copy(std::begin(ints), std::end(ints), std::back_inserter(v));
    }
    std::for_each(std::begin(v), std::end(v), [](int i) { std::cout << i << " "; });
    
    return 0;
}