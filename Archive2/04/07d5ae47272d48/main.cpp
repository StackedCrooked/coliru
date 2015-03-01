#include <iostream>
#include <iterator>

int main(int argc, const char** argv)
{
    int array[5] = {1, 2, 3, 4, 5};

    for(auto item: array)
    {
        std::cout << item << std::endl;
    }
   
    return 0;
}