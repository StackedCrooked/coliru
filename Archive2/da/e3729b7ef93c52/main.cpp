#include <iostream>
#include <memory>

int main () {
    std::unique_ptr<int> p(new int);
//    int x = 5;
    *p = 11;
    std::cout << "Before lambda declaration: " << *p << " (" << p.get() << ")" << std::endl;
    auto y = [p = std::move(p)]() {
        std::cout << "  lambda: p = " << *p << "(" << p.get() << ")" << std::endl;
    };
    std::cout << "After lambda definition: " << p.get() << std::endl;
    y();
    std::cout << "After lambda call: " << p.get() << std::endl;
    
    return 0;
}
