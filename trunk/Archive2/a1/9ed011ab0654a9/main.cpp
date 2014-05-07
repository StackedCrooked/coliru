#include <iostream>

using std::cout;
using std::endl;

class A {
    public:
        A() : is_default_constructed(true) { cout << "A default constructor" << endl; }
        A( int x, int y) : is_default_constructed(false) { cout << "A constructor " << x << " " << y << endl; }
        ~A() { cout << "A destructor, default_constructed: " << is_default_constructed << endl; }
    private:
        bool is_default_constructed;
};

class B : public A {
    public:
        B() : is_default_constructed(true)  { A(); cout << "B default constructor" << endl; }
        B( int x, int y ) : is_default_constructed(false) { A(x, y); cout << "B constructor " << x << " " << y << endl; }
        ~B() { cout << "B destructor, default_constructed: " << is_default_constructed << endl; }
    private:
        bool is_default_constructed;
};

int main(void) {
    B b1;
    B b2(2, 4);
    cout << "In main, after construction" << endl;
    return 0;
}