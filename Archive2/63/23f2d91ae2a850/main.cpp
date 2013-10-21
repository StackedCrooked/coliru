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
    
    
ierd
    std::cout << "VAR1 and VAR2 not defined" << std::endl;
#else
    std::cout << "VAR1 or VAR2 defined" << std::endl;   
#endif

    std::cout << "..................................." << std::endl;
    
#if !defined(VAR1) && !defined(VAR2)
    std::cout << "VAR1 and VAR2 not defined" << std::endl;
#else
    std::cout << "VAR1 or VAR2 defined" << std::endl;   
#endif
    
    
    std::cout << "..................................." << std::endl;
}
