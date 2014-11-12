#include <iostream>

template<typename T>
class A {
public:
    constexpr A() {};
    ~A() {};
};

class B: public A<int> {
public:
    static constexpr int a[] = {1,2,3,4,5};
    constexpr B();
    ~B();
};

constexpr B::B() {}
B::~B() {}

int main() {

}