#include <iostream>
#include <utility>

int forward(int& i)
{
    std::cout << "lvalue: ";
    return i;   
}

int&& forward(int&& i)
{
    std::cout << "rvalue: ";
    return std::forward<int&&>(i);    
}

int*&& forward(int*&& ptr_i)
{
    std::cout << "rvalue ptr: ";
    return std::forward<int*&&>(ptr_i);   
}

int*& forward(int*& ptr_i)
{
    std::cout << "lvalue ptr: ";
    return std::forward<int*&>(ptr_i);   
}

const int* forward(const int* const  ptr_to_const)
{
    std::cout << "const ptr to lvalue: ";
    return std::forward<const int* const>(ptr_to_const);
}

int main()
{
    int i = 1;
    
    const int j = 13;
    
    int* ptr_i = &i;

    const int * const  const_ptr_const_i = &j;
    
    int * const const_ptr_i = &i;

    
    std::cout << forward(0) << std::endl;
    std::cout << forward(i) << std::endl;
    std::cout << forward(ptr_i) << std::endl;
    std::cout << forward(&i) << std::endl;
    
    //These two are the same by nature; note the variables they point to are different.
    std::cout << forward(const_ptr_const_i) << std::endl;
    std::cout << forward(const_ptr_i) << std::endl;
    
    std::cout << "Cannot have a const pointer to a const rvalue because you can't really have a const pointer to a temporary/disappearing/ephermal rvalue." << std::endl;
    
    
    return 0;
}