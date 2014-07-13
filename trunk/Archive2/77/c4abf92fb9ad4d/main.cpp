#include <vector>
#include <iostream>
#include <algorithm>

bool comp (int i, int j) { return (i > j); }

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector)
{
    long size = vector.size();
    os << "vector[" << size << "] ";
    for(size_t i = 0; i < size; ++i)
        os << vector[i] << " ";
    return os;
}

int main()
{
    std::vector<int> x = {1, 2, 5, 5, 7, 2, 3};
    
    return 0;
}
