#include <iostream>
#include <string>

int main()
{
    std::string word;
    while (std::cin >> word)
        std::cout << "got " << word << std::endl;
}