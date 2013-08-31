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
    std::vector<std::function<void(Neuromon)>> iwas2{&Neuromon::bla, &Neuromon::foo};
};

int main() {
    Neuromon n;
    auto test = std::bind(n.iwas2[1], n);
    n.iwas2[0](n);
    test();
}
