#include <iostream>

using namespace std;

enum class A { i, j };
enum class B { m, n };

template <A>
struct Aattr {};

template<>
struct Aattr<A::i> {
    static void f() { cout << "A::i" << endl; }
};

template<>
struct Aattr<A::j> {
    static void f() { cout << "A::j" << endl; }
};

template <B>
struct Battr {};

template<>
struct Battr<B::m> {
    static void f() { cout << "B::m" << endl; }
};

template<>
struct Battr<B::n> {
    static void f() { cout << "B::n" << endl; }
};

template <A k>
void DoF() {
    Aattr<k>::f();
}

template <B k>
void DoF() {
    Battr<k>::f();
}

int main()
{
    DoF<A::i>();
    DoF<A::j>();
    DoF<B::m>();
    DoF<B::n>();
}
