#include <iostream>
#include <string>
#include <vector>


void myfunction(std::string argument)
{
    std::cout << "you entered: "<< argument << " as your argument\n";
}

void myfunction(int argument)
{
    std::cout << "AHA! you changed your argument to an int valued: " << argument << ".  Thought I wouldn't notice did you?\n";
}


int main()
{
    myfunction("My Custom Argument String");
    myfunction(17);
    return 0;
}
