#include <functional>
#include <iostream>

void stuff() {
    std::cout << "hello!\n";
}

int stuff2(int a, int b) {
    std::cout << a + b;
}

int main() {
    std::function<void()> f = stuff;
    std::function<int(int,int)> g = stuff2;
    f();
    g(2,2);
}