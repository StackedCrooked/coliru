#include <iostream>

using std::cout;
using std::endl;

class A {
    public:
        A() { cout << "A default constructor" << endl; }
        A( int x, int y) { cout << "A constructor " << x << " " << y << endl; }
        ~A() { cout << "A destructor" << endl; }
};

class B : public A {
    public:
        B() { A(); cout << "B default constructor" << endl; }
        B( int x, int y ) { A(x, y); cout << "B constructor " << x << " " << y << endl; }
        ~B() { cout << "B destructor" << endl; }
};

int main(void) {
    B b1;
    B b2(2, 4);
    cout << "In main, after construction" << endl;
    return 0;
}