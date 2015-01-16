#include <iostream>
#include <string>
#include <utility>

using namespace std;

enum class A { i, j };
enum class B { m, n };

template <A>
struct Aattr {};

template<>
struct Aattr<A::i> {
    static void f(int) { cout << "A::i" << endl; }
};

template<>
struct Aattr<A::j> {
    static void f(float) { cout << "A::j" << endl; }
};

template <B>
struct Battr {};

template<>
struct Battr<B::m> {
    static void f(string) { cout << "B::m" << endl; }
};

template<>
struct Battr<B::n> {
    static void f() { cout << "B::n" << endl; }
};

template <A k, typename... Args>
void DoF(Args&&... args) {
    Aattr<k>::f(std::forward<Args>(args)...);
}

template <B k, typename... Args>
void DoF(Args&&... args) {
    Battr<k>::f(std::forward<Args>(args)...);
}

int main()
{
    DoF<A::i>(10);
    DoF<A::j>(.5);
    DoF<B::m>("abc");
    DoF<B::n>();
}
