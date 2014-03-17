#include <iostream>
#include <vector>

using namespace std;

class X
{
public:
    X()  { cout << "X::X()" << endl; };
    ~X() { cout << "X::~X()" << endl; };
};

class Y : public X
{
public:
    Y() : X() { cout << "Y::Y()" << endl; };
    ~Y()      { cout << "Y::~Y()" << endl; };
};

int main() {
    vector<Y> a;
    a.resize(10);
    return 0;
}