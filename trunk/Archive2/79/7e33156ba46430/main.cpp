#include <iostream>

int main()
{
    int input = 1;
    int sum = 0;
    while(input)
    {
        std::cin >> input;
        std::cout << "The inputted number was: " << input << '\n';
        sum += input;
    }
    std::cout << "The sum of these numbers is " << sum << std::endl;
    
    return 0;
}