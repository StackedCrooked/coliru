#include <iostream>
#include <thread>

class A {
public:
    void foo(int n) { std::cout << n << std::endl; }
};

int main()
{
    A a;
    auto foo = std::bind(&A::foo, std::ref(a), 100);
    foo();
}
