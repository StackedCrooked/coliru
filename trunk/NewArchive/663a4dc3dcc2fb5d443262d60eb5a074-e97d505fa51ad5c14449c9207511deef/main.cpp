#include <functional>
#include <iostream>
#include <vector>

class Neuromon {
    void bla() {
        ++myvar;
        std::cout << myvar << std::endl;
    }
    void foo() {
        ++myvar;
        std::cout << myvar << std::endl;
    }
public:
    int myvar = 0;
    std::vector<std::function<void()>> iwas{std::bind(&Neuromon::bla, this), std::bind(&Neuromon::foo, this)};
};

int main() {
    Neuromon n;
    for(auto& func : n.iwas) {
        ++n.myvar;
        func();
        ++n.myvar;
    }
}
