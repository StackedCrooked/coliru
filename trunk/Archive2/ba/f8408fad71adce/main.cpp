#include <iostream>

constexpr int fib_cxpr(int idx) {
    return idx == 0 ? 0 :
           idx == 1 ? 1 :
           fib_cxpr(idx-1) + fib_cxpr(idx-2);
}

static int fib_steps(int idx) {
    return idx == 0 ? 2 :
           idx == 1 ? 2 :
           fib_steps(idx-1) + fib_steps(idx-2) + 2;
}

int main() {
    constexpr auto n = 27;
    std::cout << "steps: " << fib_steps(n) << '\n';
    
    constexpr auto fib_1 = fib_cxpr(n);
    std::cout << "fib(" << n << "): " << fib_1 << '\n';
}
