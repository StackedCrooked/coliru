#include <iostream>
#include <memory>
#include <string>

int main() {
    std::unique_ptr<std::string[]> foo (new std::string[5]);

    for (int i=0; i<5; ++i) foo[i]="a";
    for (int i=0; i<5; ++i) std::cout << foo[i] << ' ';
    std::cout << std::endl;
    
    std::cout << typeid(foo[0]).name();
    return 0;
}
