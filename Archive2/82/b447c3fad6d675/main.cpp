#include <iostream>
#include <typeinfo>

template <class A, class B>
struct FooBase {
    static void func2() {  std::cout << "func2<"<<typeid(A).name()<<", "<<typeid(B).name()<<">\n";}
};

template <class A, class B>
struct Foo : FooBase<A, B> {
    static void func() {
        std::cout << "func<_, _>\n";
    }
};

template <class B> struct Foo<int, B> : FooBase<int, B>
{
    static void func() { std::cout << "func<int, _>\n"; }
};

template <class A> struct Foo<A, bool> : FooBase<A, bool>
{
    static void func() { std::cout << "func<_, bool>\n"; }
};

template <> void Foo<char, char>::func() {
    std::cout << "func<char, char>\n";
}

int main() {
    Foo<short, short>::func();
    Foo<int, short>::func();
    Foo<short, bool>::func();
    Foo<char, char>::func();

    Foo<short, short>::func2();
    Foo<int, short>::func2();
    Foo<short, bool>::func2();
    Foo<char, char>::func2();
}
