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

bool test()
{
    return false;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    bool l_flag = false;
    if( (l_flag = test() ) == true )
    {
        std::cout << "l_flag = " << std::boolalpha << l_flag;
    }
}
