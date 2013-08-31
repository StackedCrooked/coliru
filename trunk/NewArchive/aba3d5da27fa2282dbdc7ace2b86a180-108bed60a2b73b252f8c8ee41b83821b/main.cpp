#include <functional>

struct foo {
    std::function<int()> f() {
        return [&]{ return x; };
    }
    int x;
};

int main() {
    foo bar { 0 };
    auto x = bar.f();
    return x();
}
