#include <iostream>
using namespace std;

enum E { A, B };

template <E x>
class C {
public:
    template <E y = x>
    static typename std::enable_if<y == A>::type foo() {
        cout << "A";
    }

    template <E y = x>
    static typename std::enable_if<y == B>::type goo() {
        cout << "B";
    }
};


int main() {
    C<A>::foo();
    C<B>::goo();
}
