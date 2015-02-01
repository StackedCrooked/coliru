#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdio>
class B;

class A {
public:
    std::shared_ptr<B> a_B_pointer;
};

class B {
public:
    std::shared_ptr<A> an_A_pointer;
};

int main()
{
    {
         std::shared_ptr<A> a(new A());
         std::shared_ptr<B> b(new B());
         a->a_B_pointer = b;
         b->an_A_pointer = a;
    }
    return 0;
}