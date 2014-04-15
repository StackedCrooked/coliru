#include <iostream>

template<typename ...T>
void f(T ...t) {
    struct E { E(...) {} } e{ ([&]{ 
        int x = t + 1; 
        std::cout << x << std::endl;  
    }(), 0)... };
}

int main() {
    f(1, 2, 3, 4);   
}