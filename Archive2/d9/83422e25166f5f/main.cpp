#include <vector>
#include <iostream>

struct Foo {
    Foo(int a) : m_bar(a) {}
    Foo(const Foo&) { std::cout << "Foo(const Foo&)"; }
    int m_bar;
    Foo& operator=(Foo& other) {
        m_bar = other.m_bar;
        return *this;
    }
};

int main()
{
    std::vector<Foo> buffer;
    buffer.push_back(Foo(42));
}
