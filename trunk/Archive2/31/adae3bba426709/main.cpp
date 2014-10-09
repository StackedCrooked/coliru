#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>


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
    //std::cout << words << std::endl;
    
    
    std::transform(words.begin(), words.end(), words.begin(), [](std::string a){return a+"ZZ";});
    std::cout << words << std::endl;
     
}
