#include <iostream>
#include <iterator>

int main(int argc, const char** argv)
{
    int array[5] = {1, 2, 3, 4, 5};

    for(auto i : array)
    {
        std::cout << i << "\n";
    }
   
    return 0;
}