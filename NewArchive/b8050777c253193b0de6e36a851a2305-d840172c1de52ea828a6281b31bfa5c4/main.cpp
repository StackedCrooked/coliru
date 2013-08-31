#include <iostream>
#include <vector>

struct Base {
    int b;
    virtual bool stuff() const {
        return false;
    }
    virtual void setStuff(int a) {
        b = a;
    }
};

template<typename T>
struct Derived : public Base {
    T c;
    virtual bool stuff() const {
        return true;
    }
    virtual void setStuff(T a) {
        c = a;
    }
};

int main() {
    std::vector<Base*> bases;
    Derived<int> v;
    bases.push_back(&v);
    bases[0]->setStuff(0);
    std::cout << v.b << '\n' << v.c << '\n';
}