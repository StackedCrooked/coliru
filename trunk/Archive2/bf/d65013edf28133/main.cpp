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
    
    /*const*/ std::unique_ptr<std::string> x(new std::string("qwerty"));
    std::unique_ptr<std::string> y(std::move(x));
    std::cout << "*y = '" << *y << "'\n";
    
    if (x.get() == nullptr) {
        std::cout << "x is nullptr\n";
    } else {
        std::cout << "x is not nullptr\n";
    }
}