#include <functional>
#include <iostream>
#include <vector>

namespace nmon {
    class Neuromon {
        double bla(int x) {
            ++myvar;
            std::cout << this << std::endl;
            std::cout << myvar << std::endl;
            return x;
        }
        double foo(int x) {
            ++myvar;
            std::cout << this << std::endl;
            std::cout << myvar << std::endl;
            return x;
        }
    public:
        Neuromon() {
            std::cout << this << std::endl;
        }
        int myvar = 0;
        std::vector<std::function<double(int)>> iwas{std::bind(&Neuromon::bla, this, std::placeholders::_1), std::bind(&Neuromon::foo, this, std::placeholders::_1)};
    };
}

int main() {
    nmon::Neuromon n;
    for(auto& func : n.iwas) {
        ++n.myvar;
        func(2);
        std::cout << &n << std::endl;
        std::cout << n.myvar << std::endl;
        ++n.myvar;
    }
}
