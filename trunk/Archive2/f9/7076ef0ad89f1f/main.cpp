#include <stdio.h>

class Base {
public:
    virtual void foo(int) {}
};

template <class T>
class TmplClass : public Base {
public:
    virtual void foo(int i) { foo(T(i)); }
    virtual void foo(T&& param) {
        printf("Template::Foo\n");
        bar(param);
    }
    virtual void bar(T&) {
        printf("Template::Bar\n");
    }
};

using SomeConcreteType = unsigned long long;

class Derived : public TmplClass<SomeConcreteType> {
public:
    void bar(SomeConcreteType&) {
        printf("Derived::Bar\n");
    }
};

int main() {
    Derived d;
    Base* b = &d;
    b->foo(12ULL);
}
