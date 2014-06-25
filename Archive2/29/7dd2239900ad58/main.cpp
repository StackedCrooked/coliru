#include <iostream>
#include <string>
#include <vector>

template <typename T>
class A
{
template <typename X> friend class C;
private:
    void f() { std::cout << "This is A" << std::endl; }
};

template <typename T>
class B : public A<T>
{
public:
    void f() { std::cout << "This is B" << std::endl; }
};

template <typename T>
class C
{
public:
    void f() {
        T b;
        b.A<int>::f();
    }
};

int main()
{
    C<B<int>> c;
    c.f();
}
