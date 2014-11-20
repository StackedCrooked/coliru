#include <iostream>
#include <type_traits>

template <typename T>
inline constexpr std::remove_reference_t<T> &lvalue(T &&r) noexcept {
    return static_cast<std::remove_reference_t<T> &>(r);
}

struct foo {
    foo() {
        std::cout << "*foo\n";
    }
    
    ~foo() {
        std::cout << "~foo\n";
    }
    
    foo(foo const&) = delete;
    foo(foo&&) = delete;
    
    void
    access() {
        std::cout << "I'm being touched!\n";
    }
};

struct bar {
    foo* f;
};

foo
fun() {
    return {};
}

bar
gun() {
    return {&lvalue(fun())};
}

int 
main() {
    bar b = gun();
    b.f->access();
}
