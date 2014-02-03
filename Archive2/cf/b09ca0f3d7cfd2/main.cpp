#include <utility>

template<typename T>
auto val_of(const T& t) -> decltype(std::declval<T>().val())
{
    return t.val();
}

int val_of(...)
{
    return 0;
}

struct A { int val() const { return 1; } };
struct B { int val() const { return 2; } };
struct C {  };

#include <iostream>
int main() {
    A a;
    B b;
    C c;
    std::cout << val_of(a) << val_of(b) << val_of(c);
}
    
