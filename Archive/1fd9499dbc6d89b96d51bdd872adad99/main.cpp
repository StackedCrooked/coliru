#include <iostream>

class base {
    void f() { do_f(); }
private:
    virtual void do_f() = 0;
};

class derived : base {
    void do_f() override { std::cout << "a"; }
}

int main() {
   derived d;
   base& b = d;
   b.f();
 }