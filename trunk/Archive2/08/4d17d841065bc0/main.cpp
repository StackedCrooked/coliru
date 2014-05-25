#include <iostream>
#include <utility>

template<class Func, class... Args>
auto apply(Func fn, Args&&... args) {
    return [&](auto&&... sargs) { 
        return fn
            ( std::forward<decltype(args)>(args)...
            , std::forward<decltype(sargs)>(sargs)... ); 
    };
}

auto add = [](int a, int b, int c) {
    return a + b + c;
};

int main() {
    std::cout << apply(add, 1)(2, 3)   << '\n';
    std::cout << apply(add, 3, 4, 5)() << '\n';
    std::cout << apply(add)(33, 6, 3)  << '\n';
}