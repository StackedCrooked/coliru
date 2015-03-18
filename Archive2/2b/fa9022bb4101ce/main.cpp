#include <iostream>
#include <iomanip>
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
    
    float a = .0000001f;
    float b = 10000000.f;
    float c = 1.1f;
    
    for (int i=0; i<12; i+=5)
    {
        
        std::cout << "Precision: " << i << std::endl 
        << std::setprecision(i)
        << " " << a << std::endl
        << " " << b << std::endl
        << " " << c<< std::endl
        << std::endl;
    }
    
}
