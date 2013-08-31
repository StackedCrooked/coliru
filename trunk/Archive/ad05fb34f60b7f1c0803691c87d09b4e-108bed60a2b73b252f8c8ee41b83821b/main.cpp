#include <functional>

int& f() {
    static int x = 0;
    return x;
}

struct foo {
    std::function<int()> f() {
        auto& x = ::f();
        return [&x]{ return x; };
    }
    int x;
};

int main() {
    foo bar;
    auto x = bar.f();
    return x();
}
