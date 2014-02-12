#include <stdexcept>
#include <vector>
#include <forward_list>
#include <iostream>

template<class Iterator>
int bar(Iterator begin, Iterator end)
{
    for (auto it = begin; it != end; ++it)
        (*it)++;
    return 0;
}

int main(int, char* []) {
    std::vector<int> x  = {0, 0, 0, 0};
    std::forward_list<int> y    = {0, 0, 0, 0};
    bar(x.begin(), x.begin() + 2);
    bar(y.begin(), y.end());
    
    for (auto i : x) std::cout << i;
    std::cout << '\n';
    for (auto i : y) std::cout << i;
}