#include <iostream>
#include <sstream>
 
int main()
{
    char c[10];
    std::istringstream input("This is sample text.");
    input.readsome(&c[0],5);
    input.readsome(&c[0],9);
    c[9]=0;
    std::cout<<c;
    return 0;
}