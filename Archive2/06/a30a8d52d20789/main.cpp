#include <iostream>

class base {
public:
    virtual void func() = 0;
};

class derivate : public base {
public:
    virtual void func();
};

void base::func() { std::cout << "base"; }
void derivate::func() { std::cout << "derivate "; base::func(); }


int main(int, char*[]) {
    derivate x;
    base& y = x;
    y.func();
    return 0;
}