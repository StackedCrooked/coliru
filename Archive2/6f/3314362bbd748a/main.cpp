#include <type_traits>

struct Foo {
    void foo() {}
};

struct Bar {
    void foo() {}
    void bar() {}
};

template<typename T>
T func()
{
    if (std::is_same<T, Foo>{}) Foo().foo();
    if (std::is_same<T, Bar>{}) Bar().foo();
    
    // common code
    T().bar();
    return T();
}

int main()
{
    func<Foo>();
}