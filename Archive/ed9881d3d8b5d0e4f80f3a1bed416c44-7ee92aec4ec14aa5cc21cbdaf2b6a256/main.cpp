#include <iostream>
#include <string>

int main()
{
    std::string input;
    while (std::cin >> input)
    {
        std::cout << "got " << input << std::endl;
    }
}