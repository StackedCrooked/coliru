#include <iostream>
#include <string>
 
int main()
{
    double n;
    while( std::cout << "Please, enter a number\n"
           && ! (std::cin >> n) )
    {
        std::cin.clear();
        std::string line;
        std::getline(std::cin, line);
        std::cout << "I am sorry, but '" << line << "' is not a number\n";
    }
    std::cout << "Thank you for entering the number " << n << '\n';
}