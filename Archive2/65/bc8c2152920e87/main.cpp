#include <iostream>

struct CheckDefault {
    CheckDefault() : value(false), param_default(true) {}
    CheckDefault(bool b) : value(b), param_default(false) {}
    bool value;
    bool param_default;
};

void func(int param1, CheckDefault s = CheckDefault()) {
    if (s.param_default)
        std::cout << "with default" << std::endl;
    else
        std::cout << "not default" << std::endl;
}

int main() {
    func(5);
    func(5, false);
}