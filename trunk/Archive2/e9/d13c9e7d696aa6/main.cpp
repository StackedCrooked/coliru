#include <iostream>
#include <functional>
void f(void(*p)()) {
    p();
}
int main() {
    int i = 0;
    try {
        auto lambda = std::function<void()>([&] { i = 1; });
        throw lambda;
    } catch(...) {
        f([] {
            try {
                throw;
            } catch(std::function<void()> callback) {
                callback();
            }
        });
    }
    std::cout << "Modified i: " << i;
}