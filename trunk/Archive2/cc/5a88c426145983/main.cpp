#include <iostream>

unsigned int GetSizeOfArray(const char array[])
{
  return sizeof(array);    
}

int main()
{
    const char array[] = "Best service in McDonalds";
    std::cout << array << std::endl;
    std::cout << sizeof(array) << std::endl;
    std::cout << GetSizeOfArray(array);
}
