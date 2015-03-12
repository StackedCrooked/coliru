#include <map>
#include <array>
#include <iostream>


struct IntArr2D {
    std::array<std::array<int, 2>, 2> repr;
    
    IntArr2D(const std::initializer_list<int> &il) {
        auto it = il.begin();
        repr[0][0] = *it++;
        repr[0][1] = *it++;
        repr[1][0] = *it++;
        repr[1][1] = *it++;
    }
    
    int &operator[](std::pair<size_t, size_t> indices) {
        return repr[indices.first][indices.second];
    }
};

enum Index {
    Zero,
    One
};

std::pair<size_t, size_t> operator,(Index i, Index j)
{
    return { i, j };
}

int main()
{
    IntArr2D a { 0, 1, 2, 3 };
    std::cout << a[One, Zero] << std::endl;
    return 0;
}

