#include <iostream>

class base {
public:
    void f() { do_f(); }
private:
    virtual void do_f() = 0;
};

class derived : public base {
    void do_f() override { std::cout << "a"; }
};

int main() {
   derived d;
   base& b = d;
   b.f();
 }