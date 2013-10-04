#include <iostream>

template <typename T>
void initialize(T array[], const T& value)
{
}

template <size_t index, size_t... indices, typename T>
void initialize(T array[], const T& value)
{
    array[index] = value;
    initialize<indices...>(array, value);
}

int main()
{
    int array[10];
    
    initialize<0,3,6>(array, 99);
    
    std::cout << array[0] << " " << array[3] << " " << array[6] << std::endl;
}