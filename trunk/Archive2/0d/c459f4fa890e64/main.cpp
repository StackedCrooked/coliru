#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int sumby(int interval, int max) {
    // interval * (1+2+3...+top) = sum;
    // (1+2+3...+n) == n(n+1)/2
    // we just need to know what top is. 
    // integer division handles that
    int top = max/interval;
    //we don't want to include the max in the series. 
    if (max%interval==0) {
        top -= 1;
    }
    return interval * top * (top +1) /2;
}

int main()
{
    int ceiling = 1000;
    std::cout << sumby(3, ceiling)+ sumby(5, ceiling) - sumby(15,ceiling) << std::endl;
}
