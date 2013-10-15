#include <iostream>

int main() { 
    float x = 1.6f;
    x+=0.2f;
    if (x==1.8f) {
        std::cout << "Gets here";    
    }
    
    return 0;
}



















/**
 * 
 * template<typename... Arguments>
class VariadicTemplate{
public: static const unsigned short int size = sizeof...(Arguments);
};
 * 
    VariadicTemplate<int,int,unsigned> a;
    std::cout << "VariadicTemplate<int,int,unsigned> a" << std::endl;
    std::cout << "Data types in class: " << a.size << std::endl;
    std::cout << "Data structure kost: " << sizeof(a) << " Byte" << (sizeof(a) > 1 ? "s" : "") << std::endl << std::endl;
    
    VariadicTemplate<double,float,unsigned,int,int,int,int> a2;
    std::cout << "VariadicTemplate<double,float,unsigned,int,int,int,int> a2" << std::endl;
    std::cout << "Data types in class: " << a2.size << std::endl;
    std::cout << "Data structure kost: " << sizeof(a2) << " Byte" << (sizeof(a2) > 1 ? "s" : "") << std::endl << std::endl;
 * 
 */