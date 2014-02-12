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

void StandardMethod() {
    
    std::vector<int> va{ 1, 2, 3, 4, 5 };

    std::vector<int> vb{ 6, 7, 8, 9, 10 };
    
    std::vector<int>(5) vc;
    
    for ()
        ;
            
    std::cout << vc << std::endl;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
