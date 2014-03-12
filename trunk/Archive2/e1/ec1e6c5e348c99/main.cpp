#include <iostream>

struct X {
    ~X() { std::cout << "~X destructor\n"; }
};

class Y {
public:
    Y(int, int, X const& = X())
    { std::cout << "Y constructor body\n"; }
};

void f(Y const&) {
    std::cout << "function f\n";
}

int main() {
    f(Y(0, 0));
}
