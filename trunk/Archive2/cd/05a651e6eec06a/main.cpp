#include <iostream>

void g(void* x) {
    std::cout << x << '\n';
}

template<typename R, typename... Args>
void f(R(*f)(Args...)) {
    // UB?
    void* p = &f;
    g(*static_cast<void**>(p));
}

double mult(double a, double b) {
    return a * b;
}

int main() {
    f(mult);
}
    
    