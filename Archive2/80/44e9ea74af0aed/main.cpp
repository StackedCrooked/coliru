#include <array>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
#include <chrono>
#include <cmath>
#include <exception>
#include <string>
#include <locale>
#include <complex>
#include <limits>
#include <valarray>

using namespace std;
using namespace std::chrono;

/* --------use this for rvalue exercises --------*/
struct C;
ostream& operator<<(ostream& out, const C& c) { cout << "(" << &c << ")"; return out; }
struct C {
    C() { cout << "c " << *this << endl; }
    C(const C&) { cout << "cc "<< *this << endl; }
    C(C&&) { cout << "mc " << *this<< endl; }
    ~C() { cout << "d " << *this<< endl; }
    C& operator=(const C&) { cout << "ca " << *this<< endl; return *this;}
    C& operator=(C&&) { cout << "ma "<< *this << endl; return *this; }
};
/* --------------------------------------------- */

template <typename... Args>
void foo(Args...) {
    cout << 0;
}

template <typename T>
void foo(T i) {
    cout << i;
}

template <>
void foo(int i) {
    cout << -i;
}

int main() {
    foo(1);
    return 0;
}