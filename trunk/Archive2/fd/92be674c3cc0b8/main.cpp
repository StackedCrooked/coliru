#include <iostream>
#include <memory>
#include <functional>
#include <future>
#include <utility>

int main() {
    static size_t c = 0;
    static size_t m = 0;
    std::function<int(void)> f;

    f = [&] {
        auto a = std::async(std::launch::async, f);
        auto b = std::async(std::launch::async, f);
        c++;
        return a.get() + b.get();
    };

    for (size_t i = 0; i < __LINE__; ++i) {
        try {
            c = 0;
            f();
        }
        catch (...) {
            m = std::max(c, m);
        }
    }
    
    std::cout << m;
}