#include <iostream>
#include <iterator>

int main(int argc, const char** argv)
{
    int array[5] = {1, 2, 3, 4, 5};

    for(auto pointer = std::begin(array); pointer != std::end(array); pointer++)
    {
        std::cout << *pointer << std::endl;
    }
   
    return 0;
}