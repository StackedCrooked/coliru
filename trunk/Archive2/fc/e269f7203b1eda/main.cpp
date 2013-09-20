#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <vector>

int main() 
{
    auto v = std::vector<int> { 1, 2 };
    std::initializer_list<int> i;
    auto it = std::begin(i);
    *it = begin(v);
}