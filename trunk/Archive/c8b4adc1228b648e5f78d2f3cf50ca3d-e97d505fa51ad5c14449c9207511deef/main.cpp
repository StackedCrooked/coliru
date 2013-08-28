#include <functional>
#include <iostream>
#include <vector>

class Neuromon {
    int myvar = 0;
    void bla() {
        myvar = 2;
        std::cout << myvar << std::endl;
    }
    void foo() {
        myvar = 4;
        std::cout << myvar << std::endl;
    }
public:
    //std::vector<std::function<void(Neuromon)>> iwas2{&Neuromon::bla, &Neuromon::foo};
    std::vector<std::function<void()>> iwas{std::bind(&Neuromon::bla, this), std::bind(&Neuromon::foo, this)};
};

int main() {
    Neuromon n;
    for(auto& func : n.iwas) func();
}
