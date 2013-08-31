#include <iostream>
#include <iomanip>

int main()
{
    double a = 0.0;
    double b = -0.0;
    
    std::cout << "Value comparison" << std::endl;
    std::cout << (a==b) <<std::endl;
    std::cout << (a!=b) <<std::endl;
    
    std::cout << "\nValue representation" << std::endl;
    unsigned char *pa = reinterpret_cast<unsigned char*>(&a);
    for(int i = 0 ; i < sizeof(a) ; ++i)
       std::cout << std::setw(-2) << (unsigned)pa[i] << " ";
    
    std::cout << std::endl;
    unsigned char *pb = reinterpret_cast<unsigned char*>(&b);
    for(int i = 0 ; i < sizeof(b) ; ++i)
       std::cout << std::setw(-2) << (unsigned)pb[i] << " ";
}