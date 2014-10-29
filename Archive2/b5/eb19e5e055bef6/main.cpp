#include <iostream>

struct FooWithState {
    int i = 0;
    FooWithState& operator++() { ++i; return *this; }
};

FooWithState makeAFoo() { return FooWithState{}; }

template<typename T>
void useSomethingStateful(T&& t) {
    for (int i = 0; i < 10; ++i) {
        ++t;
        std::cout << t.i << ", ";
    }
}

int main() {
    FooWithState aFoo;
    useSomethingStateful(aFoo);
    useSomethingStateful(makeAFoo());
}
