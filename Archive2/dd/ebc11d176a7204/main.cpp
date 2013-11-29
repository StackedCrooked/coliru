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

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::vector<int> v;
    int sum;
    for(int i = 1;i < 24;i++)
    {
        sum+=i;
        v.push_back(sum);
    }    
    
    std::cout<<"Fibonacci:\n"<<v<<std::endl;
    
}
