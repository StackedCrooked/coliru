#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>

using namespace std;


template <typename T>
void initialize(T array[], T value)
{
}

template <size_t index, size_t... indices, typename T>
void initialize(T array[], T value)
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

