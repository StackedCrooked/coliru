#include <iostream>
#include <thread>

using namespace std;

class Pointertest
{
public:
    Pointertest() {cout << "Constructor";}
    Pointertest(Pointertest const& pointertest) {cout << "Copy";}
    Pointertest(Pointertest&& pointertest) {cout << "Move";}
    ~Pointertest() {cout << "Destruct";}
};

void foo(Pointertest pointertest)
{
}

int main()
{
    Pointertest pointertest;
    thread test(foo, std::move(pointertest));
    test.join();
}
