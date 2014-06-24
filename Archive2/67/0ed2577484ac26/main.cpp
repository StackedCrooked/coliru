#include <iostream>
#include <functional>

class C {
  public:
    int get(int x) { return x*x; }
};

struct S {
    std::function<int(int)> func;
};

int main() {
    C c;
    S s;

    std::cout << c.get(3) << std::endl;

    s.func = std::bind(&C::get, &c, std::placeholders::_1);
    std::cout << s.func(3) << std::endl;

    return 0;
}
