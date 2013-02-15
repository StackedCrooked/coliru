#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<int> divisors(int n)
{
    if (n == 0) return {};
    if (n == 1) return {1};
    
    std::vector<int> result = {1};
    
    for (int i = 2; i <= n/2; ++i)
    {
        if (n % i == 0) result.push_back(i);
    }
    
    result.push_back(n);
    return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T> & v)
{
    s << "[ ";
    for (const auto & t : v) s << t << " ";
    return s << ']' << std::endl;
}


int main()
{
    std::cout << divisors(1);
    std::cout << divisors(3);
    std::cout << divisors(6);
    std::cout << divisors(10);
    std::cout << divisors(15);
    std::cout << divisors(21);
    std::cout << divisors(28);
}