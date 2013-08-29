#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
 
int bla(int za)
{
}

int main()
{
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '),
               str1.end());
    std::cout << str1 << '\n';
    int* p = nullptr;
    *p = 2;
}