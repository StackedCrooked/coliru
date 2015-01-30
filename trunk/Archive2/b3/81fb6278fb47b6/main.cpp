#include <iostream>
#include <typeinfo>

typedef void fn();

void fn_takes_fn(fn x) {
    std::cout << typeid(x).name() << ", " << typeid(fn).name() << std::endl;
}

int main() {
    fn_takes_fn([](){std::cout << "??" << std::endl;});
    return 0;
}