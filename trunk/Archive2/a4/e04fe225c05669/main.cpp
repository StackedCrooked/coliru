#include <iostream>

void f(unsigned int array[])
{
    std::cout << "Size of array is: " << sizeof(array) << std::endl;
}
 
int main()
{
    unsigned int array[] = {1,2,3,4};
    std::cout << "Size of array is: " << sizeof(array) << std::endl;
    f(array);
}