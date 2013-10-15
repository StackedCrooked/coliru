#include <iostream>

decltype(auto) foo() {
    struct return_type {
        int a, b;
        bool c;
    };
    return return_type{1,2,false};
}

int main() {
    auto result = foo();
    std::cout << result.a << ' ' <<  result.b << ' ' << result.c;
}