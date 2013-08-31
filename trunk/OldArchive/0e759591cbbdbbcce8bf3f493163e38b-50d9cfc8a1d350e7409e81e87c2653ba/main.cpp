#include <iostream>


void func_a() {
    std::cout << "a" << std::endl;
}

void func_b() {
    std::cout << "b" << std::endl;
}


struct A {};
struct B {};

template<typename T>
struct Test {
    void func() {
        std::cout << "some other type" << std::endl;
    }
};


// Specialization for A
template<>
void Test<A>::func() {
    func_a();
}

// Specialization for B
template<>
void Test<B>::func() {
    func_b();
}


int main() {
    Test<A> a;
    Test<B> b;
    Test<int> i;
    
    a.func();
    b.func();
    i.func();
}