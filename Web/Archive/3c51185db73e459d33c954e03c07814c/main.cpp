#include <iostream>
#include <sstream>

int main()
{
    std::string s="8978x9";
    std::stringstream ss(s);
    int x;
    if ( ss >> x )
    {
        std::cout << x << " is not same as " << s << std::endl;
    }
}