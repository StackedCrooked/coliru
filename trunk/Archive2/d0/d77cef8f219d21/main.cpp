#include <iostream>
using namespace std;

enum E { A, B };

template <E x>
class C {
public:
    template <E y = x, class enabled = typename std::enable_if<y == A>::type>
    static void foo() {
        cout << "A";
    }

    template <E y = x, class enabled = typename std::enable_if<y == B>::type>
    static void goo() {
        cout << "B";
    }
};


int main() {
    C<A>::foo();
    C<B>::goo();
}
