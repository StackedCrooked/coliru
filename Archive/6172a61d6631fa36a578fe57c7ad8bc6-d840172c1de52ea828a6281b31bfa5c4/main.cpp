#include <vector>
#include <iostream>

class Base {
public:
    virtual ~Base() {}
    virtual bool stuff() { return false; };
};

class Derived : public Base {
public:
    bool stuff() {
        return true;
    }
    
    virtual ~Derived () {
        std::cout << "Oh bby~" << std::endl;
    }
};

class OtherClass {
public:
    std::vector<Base*> bases;
};

int main() {
    OtherClass o;
    Derived d;
    o.bases.push_back( &d );
    if(o.bases[0]->stuff())
        std::cout << "..." << std::endl;
}