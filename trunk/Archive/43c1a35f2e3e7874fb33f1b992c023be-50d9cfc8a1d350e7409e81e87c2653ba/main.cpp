#include <typeinfo>
#include <iostream>


int main()
{
    int i;
    int* p_i;
    auto arr = new int[3][4];
    
    std::cout << typeid(arr).name() << std::endl;;
    std::cout << typeid(i).name() << std::endl;
    std::cout << typeid(p_i).name() << std::endl;
    
    delete[] arr;   // This is somehow deleting the first dimension (int**)
}