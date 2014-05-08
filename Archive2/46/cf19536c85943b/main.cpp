#include <iostream>
using namespace std;

class A {
    static const auto x = 1;
public:
    friend void h(A&) {}
    friend void g() {}
    friend void k();
    A() {
        h(*this);   // 0
        g();        // 1
        k();        // 2
    }
};
     
void k() { (void)A::x; }
 
int main() {
    A a;
    h(a); // 3
    g();  // 4
    k();  // 5
}