#include <iostream>

template <typename T>
class BVal {
public:
    BVal(T val) : tmp(val) { }
    
    T tmp;
};

BVal<int> getCostam() { 
    return 20;   
}

int main()
{
    std::cout << getCostam().tmp << std::endl;
    return 0;   
}