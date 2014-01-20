#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss;
    ss << "+1234";
    
    char sign;
    std::cout << "Enter '+' for addition or '-' for subtraction: ";
    ss.get(sign);
    if ( sign != '+' && sign != '-' ) {
        std::cout << "you can only enter '+' or '-'!\n";
        return 1;
    }
    
    return 0;
}