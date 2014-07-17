#include <iostream>

class A {
public:
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
};

class B{
public:
    B(const A& a)
        : a{a}
    { }
private:
    const A& a;
};

int main()
{
    std::cout << __VERSION__;
    A a{};
    B b{a};
}