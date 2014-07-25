#include <iostream>
#include <functional>

using namespace std;

class A {
    std::function<void(void)> f;
public:
    A(std::function<void(void)> pf) : f(pf) {}
    void callf() { f(); }
};

class B {
    A *a;
public:
    void test() {
        B *that = this;
        auto f = [this, that]() {
            cout << "this: " << this << " that: " << that << endl;
            delete this->a;
            cout << "this: " << this << " that: " << that << endl;
        };

        a = new A(f);
        a->callf();
    }
};

int main()
{
    B().test();
}