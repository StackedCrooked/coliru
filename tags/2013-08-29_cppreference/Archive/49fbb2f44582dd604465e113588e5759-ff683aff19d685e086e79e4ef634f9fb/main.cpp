#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
std::vector<T> operator +(std::vector<T> &lhs, std::vector<T> &rhs)
{
    std::vector<T> temp;
    temp.insert(temp.end(), lhs.begin(), lhs.end());
    temp.insert(temp.end(), rhs.begin(), rhs.end());
    
    return temp;
}

int main()
{
    std::vector<int> x{1, 2, 3}, y{4, 5, 6};
    
    std::vector<int> z(x + y);
    
    for (auto a : z)
        std::cout << a << ' ';
}