#include <functional>
#include <iostream>
#include <vector>

class Neuromon {
    void bla() {
        ++myvar;
        std::cout << this << std::endl;
        std::cout << myvar << std::endl;
    }
    void foo() {
        ++myvar;
        std::cout << this << std::endl;
        std::cout << myvar << std::endl;
    }
public:
    Neuromon() {
        std::cout << this << std::endl;
    }
    int myvar = 0;
    std::vector<std::function<void()>> iwas{std::bind(&Neuromon::bla, this), std::bind(&Neuromon::foo, this)};
};

int main() {
    Neuromon n;
    for(auto& func : n.iwas) {
        ++n.myvar;
        func();
        std::cout << &n << std::endl;
        std::cout << n.myvar << std::endl;
        ++n.myvar;
    }
}
