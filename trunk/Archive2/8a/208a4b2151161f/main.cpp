#include <iostream>

template<typename ...T>
void f(T ...t) {
    struct E { E(...) {} int i{}; } _, e{ ([&](int i) { 
        int x = t + 1; 
        std::cout << x << i << std::endl;  
    }(_.i++), 0)... };
}

int main() {
    f(1, 2, 3, 4);   
}