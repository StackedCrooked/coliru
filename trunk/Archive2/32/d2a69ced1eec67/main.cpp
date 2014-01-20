#include <iostream>
#include <thread>

class A {
public:
    void foo(int n) { std::cout << n << std::endl; }
};

int main()
{
    A a;

    std::thread t1(&A::foo, std::ref(a), 100);
    t1.join();
}
