#include <iostream>
using namespace std;

namespace A {
    void foo() { cout << "A::foo" << endl; }
}

namespace B {
    namespace A {
        void foo() { cout << "B::A::foo" << endl; }
    }
    void g() { ::A::foo(); }
}

int main() {
    B::g();
}
