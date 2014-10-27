#include <iostream>

struct A {
    A& operator=(A& rhs) const {rhs.value = value; return rhs;}
    int value;
};

int main() {
    A a1{1};
    const A a2{};
    a2=a1;
    std::cout << a1.value << '\n';
}