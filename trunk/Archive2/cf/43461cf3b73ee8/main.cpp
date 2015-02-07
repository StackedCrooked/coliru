#include <iostream>
#include <functional>
using namespace std;

typedef std::function<void(int)> F;

class testClass {
public:
    void f1();
    void f2(int i);

} foo;

void f0(F f) {
    (f)(1337); // f = a pointer to f2, which is sent from f1
}

void testClass::f2(int i) {
    cout << i;
}

void testClass::f1() {
    f0(std::bind(&testClass::f2, this, std::placeholders::_1));
}

int i;
int main() {
    foo.f1(); // I want foo.f1 to call f0 which should call foo.f1()
    cin >> i;
}
