#include <iterator>
#include <iostream>

int main()
{
    constexpr std::size_t size = 10;
    
    int* pointerToArray = new int[size];
    
    auto& arrayRef = *reinterpret_cast<int(*)[size]>(pointerToArray);
    
    std::cout <<  (std::end(arrayRef) - std::begin(arrayRef)) << std::endl;
}
