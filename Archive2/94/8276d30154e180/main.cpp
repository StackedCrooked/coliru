#include <iostream>
#include <memory>
#include <utility>
#include <string>
 
int main()
{
    const std::shared_ptr<std::string> p1(new std::string("asdf1234"));
    std::shared_ptr<std::string> p2(p1);
    std::cout << "*p1 = '" << *p1 << "'\n";
    std::cout << "*p2 = '" << *p2 << "'\n";
}