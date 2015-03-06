#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <random>

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
    std::list<std::string> strings = {"test1", "test2", "test3"};
    for (auto& s : strings)
    {
        std::cout << s << std::endl;
    }
    
    std::random_device rnd;
    std::cout << rnd.entropy() << std::endl;
    std::cout << rnd.min() << std::endl;
    std::cout << rnd.max() << std::endl;
    std::cout << rnd() << std::endl;
    
    return 0;
}
