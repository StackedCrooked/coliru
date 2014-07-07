#include <iostream>

template<class T> struct foo;

template <typename T>
typename foo<T>::type f(int) { std::cout << "0"; }

template <typename T>
void f(...) { std::cout << "1"; }

void g() {
    f<int>(0);
}

template<class T> struct foo { using type = void; };

int main()
{
    g();
    f<int>(0);
}