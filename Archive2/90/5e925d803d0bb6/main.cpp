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
    
    

    std::vector<double> x(256,0);
    
    long long int ptr = (long long int)(&x[0]);
    
    std::cout << "Pointer address: " << static_cast<void*>(&x[0]) << ", or in base10: " << ptr << std::endl;
    
    if ( (ptr & 15) == 0) {
        std::cout << "Memory is 16-byte aligned" << std::endl;
    } else {
        std::cout << "Memory is NOT 16-byte aligned" << std::endl;
    }    
}
