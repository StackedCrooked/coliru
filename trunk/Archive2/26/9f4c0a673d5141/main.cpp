#include <iostream>
using namespace std;

enum E { A, B };

class C_base {};

template <E x>
class C : public C_base {};

template <>
class C<A> : public C_base {
public:
    static void foo() {
        cout << "A";
    }
};

template <>
class C<B> : public C_base {
public:
    static void goo() {
        cout << "B";
    }
};

int main() {
    C<A>::foo();
    C<B>::goo();
}
