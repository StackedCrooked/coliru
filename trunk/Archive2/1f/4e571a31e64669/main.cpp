#include <memory> // std::unique_ptr
#include <iostream>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct test {
    test() { std::cout << "constructed\n"; }
    ~test() { std::cout << "destructed\n"; }
    test(test&&) { std::cout << "moved\n"; }
    test(const test&) { std::cout << "copied\n"; }
    void print() { std::cout << "...\n"; }
};

int main() {
    auto f = make_unique<test>();
    f->print();
}