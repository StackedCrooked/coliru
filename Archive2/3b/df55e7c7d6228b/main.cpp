#include <utility>
#include <new>
#include <cassert>

template <typename T, typename... Args>
void ctor(void* ptr, Args&&... args) {
    ::new (ptr) T(std::forward<Args>(args)...);
}

using default_ctor_t = void(*)(void*);

struct foo {
    int i = 1;
};

struct bar {
    int i = 2;
};

default_ctor_t foo_ctor = &ctor<foo>;
default_ctor_t bar_ctor = &ctor<bar>;

void make(default_ctor_t c, void* ptr) {
    return c(ptr);
}

int main() {
    union {
        int i;
        foo dummy0;
        bar dummy1;
    } x = { 0 }, y = { 0 };

    make(foo_ctor, &x);
    assert(x.i == 1);
    make(bar_ctor, &y);
    assert(y.i == 2);
}