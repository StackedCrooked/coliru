#include <iostream>
using namespace std;
class A {
    public :

    A() {
        cout<<"\nIn A const.";
    }

    ~A() {
        cout<<"\nIn A dest.";
    }
};

class B : public A {
    public :

    B() {
        cout<<"\nIn B const.";
    }

    ~B() {
        cout<<"\nIn B dest.";
    }
};

int main() {
    A a;
    B b;
}