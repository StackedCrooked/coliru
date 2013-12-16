#include <functional>
#include <vector>
#include <iostream>

void f1(int x) {
    std::cout << x << '\n';
}

void f2(int x) {
    std::cout << x << '\n';
}

void f3(int x) {
    std::cout << x << '\n';
}

using function_vector = std::vector<std::function<void(int)>>;

void callFunctions(function_vector& vec) {
    for (auto& f : vec)
        f(1);
}

int main() {
    function_vector vec = { &f1, &f2, &f3 };
    callFunctions(vec);
}