#include <iostream>

// A just holds a value - it's public so I don't have to write a get/set pair.
class A {
public:
    int val;
    A(int _val): val(_val) {}
};

// B holds a reference to an A, and provides some sort of API that involves mutating A.
class B {
    A& ref;
public:
    B(A& _ref): ref(_ref) {}
    void incA() { ref.val++; }
};

// This method promises not to modify a, but it does, through b.
static void oops(const A& a, B& b) {
    b.incA();
}

int main(void) {
    A a(5);
    B b(a);
    oops(a, b);
    std::cout << a.val << "\n";
    return 0;
}