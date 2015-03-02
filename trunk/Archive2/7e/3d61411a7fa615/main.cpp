#include <iostream>

template<typename F>
void invoke(F f) {
    f(10);
}

void one(int x) {
    std::cout << x * 2 << '\n';
}

struct two {
    void operator()(int x) {
        std::cout << x * 10 << '\n';
    }
};

int main() {
    invoke(one);
    invoke(two{});
}