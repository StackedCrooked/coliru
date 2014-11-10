#include <iostream>

using namespace std;

struct B {
    virtual ~B() = default;
    virtual B& operator=(const B& b) = 0;
    virtual int value() const = 0;
};

struct D : B {
    int x;
    D(int y) : x(y) {}
    B& operator=(const B& b) {
        x = b.value();
        return *this;
    }
    int value() const { return x; }
};

int main()
{
    B* d = new D(3);
    B* dd = new D(5);
    *d = *dd;
    cout << d->value() << "  " << dd->value() << endl;
    delete d;
    delete dd;
    return 0;
}
