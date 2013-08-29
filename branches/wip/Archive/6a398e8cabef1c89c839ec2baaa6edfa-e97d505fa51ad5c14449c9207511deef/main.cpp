#include <functional>
#include <iostream>
#include <vector>

class Neuromon {
    int myvar;
    void bla() {};
    void foo() {};
public:
    std::vector<void(Neuromon::*)()> iwas{&Neuromon::bla, &Neuromon::foo};
    std::vector<std::function<void(Neuromon)>> iwas2{&Neuromon::bla, &Neuromon::foo};
};

int main() {
    Neuromon n;
    n.iwas2[0](n);
}
