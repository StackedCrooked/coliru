#include <new>
#include <iostream>


int main()
{
    int a = 1, b = 2;
    
    int* aa = new (&a) int();
    int* bb = new (&b) int;
    
    std::cout << *aa << *bb << std::endl;
}