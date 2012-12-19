#include <iostream>
#include <utility>


int main()
{
    std::cout << sizeof(std::pair<char, std::pair<short, std::pair<int, long>>>) << std::endl;
    std::cout << sizeof(std::pair<std::pair<std::pair<long, int>, short>, char>) << std::endl;
    return 0;
}