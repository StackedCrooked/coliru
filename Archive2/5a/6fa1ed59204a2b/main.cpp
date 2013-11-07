#include <iostream>
#include <vector>
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

void printit(int a)
{
    std::cout << a << "yaaaarrrr" << std::endl;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

    std::vector<int> a;
    
    for (int counter = 0; counter < 100; counter++)
    {
        a.push_back(counter);
    }
    
    std::for_each(a.begin(), a.end(), printit);
    
}
