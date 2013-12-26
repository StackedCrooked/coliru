#include <iostream>

struct Type_A {};
struct Type_B {};
struct Type_C {};

struct Type_D {};
struct Type_E {};
struct Type_F {};

struct Category1 {};
struct Category2 {};

template<class T>
struct Category;

template<>
struct Category<Type_A> : Category1 {};
template<>
struct Category<Type_B> : Category1 {};
template<>
struct Category<Type_C> : Category1 {};

template<>
struct Category<Type_D> : Category2 {};
template<>
struct Category<Type_E> : Category2 {};
template<>
struct Category<Type_F> : Category2 {};

template<class T>
void foo(Category1, T)
{
    std::cout << "Category1\n";
}

template<class T>
void foo(Category2, T)
{
    std::cout << "Category2\n";
}

template<class T>
void foo(T x)
{
    foo(Category<T>(), x);
}

int main() {
    foo(Type_A());
    foo(Type_E());
}
