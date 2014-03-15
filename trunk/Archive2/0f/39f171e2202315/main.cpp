#include <iostream>

template<class T>
struct A
{
    T m[2];
    void print() { std::cout << "A\n"; }
};

template<class T>
struct B
{
    T* m;
    void print() { std::cout << "B\n"; }
};

template<class T, class = T[]>
A<T> foo(int) { return {}; }

template<class T>
B<T> foo(...) { return {}; }


struct base
{
    virtual void a() = 0;
};
struct derived : base
{
    virtual void a() override;
};

int main()
{
    foo<base>(0).print();
    foo<derived>(0).print();
}