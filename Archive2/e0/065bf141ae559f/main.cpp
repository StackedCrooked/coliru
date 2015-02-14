#include <iostream>
#include <algorithm>

int main()
{
    char array[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    std::replace(std::begin(array), std::end(array), 'a', 'z');
    for(char c: array)
        std::cout << c;
}
