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

struct A{
    static const int a = 1;
    static constexpr double b = 2.;
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
  
  std::cout << "a= "<< A::a << std::endl;
  std::cout << "b= "<< A::b << std::endl;
  


        
}