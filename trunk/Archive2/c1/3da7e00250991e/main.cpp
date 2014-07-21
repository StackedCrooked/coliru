#include <iostream>

struct base {
private:
    int x;
public:
    base& test(int t) { x = t; return *this; }
};

struct derived : public base {
private:
    int y;
public:
    derived& other(int t) { y = t; return *this; }
};

int main() {
    derived d;
    d.test(10).other(25);
}