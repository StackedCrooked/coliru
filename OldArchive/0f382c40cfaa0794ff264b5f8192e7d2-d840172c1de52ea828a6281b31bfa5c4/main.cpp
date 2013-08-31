#include <vector>
#include <iostream>

class Base {
public:
    virtual ~Base() {}
    virtual bool stuff() = 0;
};

class Derived : public Base {
public:
    bool stuff() {
        return true;
    }
};

class OtherClass {
public:
    std::vector<Base> bases;
};

int main() {
    OtherClass o;
    Derived d;
    o.bases.push_back(d);
    if(o.bases[0].stuff())
        std::cout << "...";
}