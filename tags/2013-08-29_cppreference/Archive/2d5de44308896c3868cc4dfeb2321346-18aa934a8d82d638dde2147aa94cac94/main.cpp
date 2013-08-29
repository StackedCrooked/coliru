#include <iostream>
#include <sstream>

int main()
{
    std::string s="89789 x";
    std::stringstream ss(s);
    int x;
    char y;
    if ( ss >> x)
    {
        if  (!(ss >> y))
            std::cout << x << " is the same as " << s << std::endl;
        else 
            std::cout << "Failed to convert string to int: junk in input: " << y  << std::endl;
    }
}