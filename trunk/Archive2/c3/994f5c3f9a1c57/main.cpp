#include <iostream>
#include <typeinfo>


template<typename T> void foo(T t)   { std::cout << typeid(t).name() << "\n"; }
template<typename T> void bar(T&& t) { std::cout << typeid(t).name() << "\n"; }

// struct {} _ = "test";

int main()
{
    foo("text");
    bar("text");
}
