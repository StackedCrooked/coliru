#include <functional>
#include <iostream>

void f(int a = 10, int b = 20, int c = 30, int d = 40) {
    std::cout << a << ',' << b << ',' << c << ',' << d << '\n';
}

int main() {
    using namespace std::placeholders;
    std::function<void(int, int)> g = std::bind(f, _1, 20, _2, 40);
    g(50, 100);
    
    // Lambda version
    
    auto h = [](int x, int y) { f(x, 20, y, 40); };
    
    h(100, 50);
}