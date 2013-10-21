#include <iostream>
using namespace std;

class X {
public:
    X() { cout << "X created" << endl; }
    ~X() { cout << "X destroyed" << endl; }
};

int main() {
    X *p = new X;
    delete[] p;
}