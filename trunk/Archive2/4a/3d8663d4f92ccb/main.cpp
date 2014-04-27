#include <iostream>

template<typename Return, typename... Args>
struct f {
    Return(*func)(Args...);
    int test(Args&&... args) {
        Return t = func(std::forward<Args>(args)...);
        return 1;
    }
};

void lol(int) {}

int main() {
    f<void, int> t;
    t.func = lol;
    std::cout << t.test(10);
}