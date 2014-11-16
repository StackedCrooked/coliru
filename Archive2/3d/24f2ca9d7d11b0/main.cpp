#include <iostream>

using namespace std;

class A {
public:
    int p;
    A() {
        cout << "Inside A constr" << endl;
    }
    A(const A& a) {
        cout << "Inside copy constr" << endl;
    }
    A* operator=(const A& b) {
        cout << "Inside assignment oper" << endl;
    }
};

A f1() {
    cout << "Inside f1" << endl;
    A a;
    cout << "Just before return from f1" << endl;
    return a;
}

int main() {

    A x = f1();
    return 0;
}