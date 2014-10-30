#include <iostream>

template <typename T, typename D>
struct foo {
    T* ptr;
    D deleter;
    
    foo(int, D d) : deleter{d} { }
};

template <typename T, typename D>
struct bar : private D {
    T* ptr;
    
    bar(int, D d) : D{d} { }
};

int
main() {
    int i = 5;
    auto del = [] { };
    
    foo<int, decltype(del)> x{i, del};
    bar<int, decltype(del)> y{i, del};
    
    std::cout << sizeof(x) << ", " << sizeof(y) << '\n';
}
