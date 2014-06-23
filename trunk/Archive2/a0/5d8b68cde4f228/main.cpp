#include <cstdio>

struct base {
    base& f() {
        return *this;
    }
};

struct derived : base {
    derived& g() {
        return *this;
    }
};

int main() {
    derived x;
    x.f().g();
}