#include <string>
#include <iostream>

void myFunction(const std::string& s)
{std::cout << s;}

int main() {  
    char charVar = 'A';
    int x1 = 3;
    int x2 = -17;
    myFunction("the char is: " + std::string(&charVar) + ", int1: " + std::to_string(x1) + ", int2: " + std::to_string(x2) + " and that's it!");
}