#include <iostream>
#include <string>
#include <vector>


void myfunction(std::string argument)
{
    std::cout << "you entered: "<< argument << " as your argument\n";
}


int main()
{
    myfunction("My Custom Argument String");
    myfunction("Another argument");
    return 0;
}
