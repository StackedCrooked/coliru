#include <iostream>

template<typename T_>
struct Foo {
    Foo( T_ v ) : v_{v} {}
    
    T_ v_ {};
    
    void display() { std::cout << v_ << " "; }
};

extern template struct Foo<int>; // 1
template struct Foo<int>; // 2

int main() {
    Foo<int>{42}.display();
}
