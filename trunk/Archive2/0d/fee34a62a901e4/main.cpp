#include <iostream>
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
