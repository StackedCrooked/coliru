#include <random>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::mt19937 eng(std::random_device {}());
    
    int myArray[] = {1, 2, 3, 4, 5};
    std::size_t N = 5;
    
    std::shuffle(myArray, myArray + N, eng);
    
    for (auto i : myArray)
        std::cout << i << ", ";
}