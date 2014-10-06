#include <string>
#include <iostream>

int main()
{
    unsigned char myVar[10] = "abcdefg";
    std::string res(myVar, myVar + 7);
    std::cout << res;
}