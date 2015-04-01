#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>

int main()
{
    auto d = std::deque<int>{1, 2, 3};
    
    auto const it = std::find(std::begin(d), std::prev(std::end(d)), 3);

    std::cout << (it != std::end(d));
}