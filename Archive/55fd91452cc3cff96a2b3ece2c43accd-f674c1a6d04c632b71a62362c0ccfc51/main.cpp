#include <string>
#include <iostream>


void func(const std::string& str) {
    [=]() mutable {
        str = "New string!";
        std::cout << str;
    }();
}



int main()
{
    std::string str("Hello World");
    func(str);
}