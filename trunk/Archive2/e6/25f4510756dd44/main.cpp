#include <iostream>

int main()
{
    int n = 123;
    bool b = *reinterpret_cast<bool*>(&n); // UB!
    
    if (b == true) std::cout << "b is true" << std::endl;
    if (b == false) std::cout << "b is false" << std::endl;
}

