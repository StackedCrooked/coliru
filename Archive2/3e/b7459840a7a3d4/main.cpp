#include <iostream>

using std::cout;
using std::endl;

struct A
{ 
    A(){ cout << "A" << endl; }
    ~A(){ cout << "~A" << endl; }
};

struct B
{ 
    B(){ cout << "B" << endl; }
    ~B(){ cout << "~B" << endl; }
    void destroyer()
    {
        delete &a;
    }
    A a;
};

int main() {
    B *b = new B();
    b->destroyer();
    delete b;
}