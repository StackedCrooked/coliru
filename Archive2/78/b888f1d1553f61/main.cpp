#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    
    std::vector<std::vector<int> > vec = { {3,1,2}, {5,4,6} };
    
    std::for_each(std::begin(vec), std::end(vec), [](auto &v) { std::sort(std::begin(v), std::end(v));});
    std::sort(std::begin(vec), std::end(vec), [](auto &v1, auto &v2) { return v1[0] < v2[0];});
    std::cout << vec << std::endl;
    return 0;
}
