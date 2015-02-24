#include <iostream>
#include <string>



int main()
{
   std::string postal_code;

    std::cout << "Enter postal code: ";
    std::getline( std::cin, postal_code);
    std::cout << "Your postal code is: " << postal_code << std::endl;
}
