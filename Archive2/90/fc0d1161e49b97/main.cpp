#include <functional>
#include <iostream>

template <typename Tr, typename... TArgs>
using TStub = Tr (*)(void*, TArgs...);

template <typename Tr, typename... TArgs>
using TFunc = Tr (*)(TArgs...);

template <typename Tr, typename... TArgs>
struct foo {
    foo(TFunc<Tr, TArgs...> f)
        : callback{[&] (void*, TArgs... args) { return f(args...); }}
    { }
    
    std::function<Tr(void*, TArgs...)> callback;
};

void
f(int i) {
    std::cout << i << '\n';
}

int
main() {
    foo<void, int> x{&f};
    x.callback(nullptr, 4);
}
