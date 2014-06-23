#include <vector>
#include <iostream>
#include <algorithm>

bool comp (int i, int j) { return (i > j); }

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector)
{
    long size = vector.size();
    ostr << "vector[" << size << "] ";
    for(int i = 0; i < size; ++i)
        ostr << vector[i] << " ";
    return os;
}

int main()
{
    std::vector<int> x = {1, 2, 5, 5, 7, 2, 3};
    std::vector<int> y(x);
    std::sort(y.begin(), y.end(), comp);
    auto remove = std::unique(y.begin(), y.end());
    y.erase(remove, y.end());
    
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    
    int sum_x = std::accumulate(x.begin(), x.end(), 0);
    int sum_y = std::accumulate(y.begin(), y.end(), 0);
    
    std::cout << "sum_x: " << sum_x << std::endl;
    std::cout << "sum_y: " << sum_y << std::endl;
    
    int mean_x = sum_x / x.size();
    int mean_y = sum_y / y.size();
    
    std::cout << "mean_x: " << mean_x << std::endl;
    std::cout << "mean_y: " << mean_y << std::endl;
    
    return 0;
}
