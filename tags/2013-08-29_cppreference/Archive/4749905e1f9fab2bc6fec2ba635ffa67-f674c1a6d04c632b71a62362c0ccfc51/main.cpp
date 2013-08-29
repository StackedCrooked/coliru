#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    auto mafunc = [&os](const std::string&  s) -> bool {os << s << std::endl; return true;};
    
    std::for_each(vec.begin(), vec.end() , [&os](const std::string&  s)
    {os << s << std::endl;}
    );
    
    for(auto s : vec)
    {
        mafunc(s);
    }
    
    return os;
}


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
