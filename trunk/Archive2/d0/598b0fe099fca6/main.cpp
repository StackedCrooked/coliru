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
    
    std::vector<int> f = { 1, 1, 2, 3, 5, 8, 13, 21 };
    
    // Creamos la Lambda
    auto imprime = [](int numero) -> void
    {
        std::cout << numero << ": " << std::string(numero, '*') << '\n';
    };
 
    for (auto n : f)
    {
        // Usamos la Lambda
        imprime(n);
    }     
}
