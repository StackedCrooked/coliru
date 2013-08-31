#include <vector>
#include <iostream>

class Base {
public:
    virtual ~Base() {}
    virtual bool stuff() = 0;
};

template<typename T>
class Derived : public Base {
public:
    T value = T();
    bool stuff() {
        std::cout << value << '\n';
        return true;
    }
};

class OtherClass {
public:
    std::vector<Base*> bases;
};

int main() {
    OtherClass o;
    Derived<int> d;
    o.bases.push_back(&d);
    if(o.bases[0]->stuff())
        std::cout << "...";
}