#include <iostream>
#include <string>

class Base {
public:
    Base() {}
    virtual ~Base() {}
    virtual std::string text() const {
        return "Base";
    }
};

class Derived: public Base {
public:
    Derived(Base& _b): b(_b) {
        std::cout << "********" << std::endl;
    }
    virtual ~Derived() {}
    virtual std::string text() const {
        return b.text() + " - Derived";
    }

private:
    Base& b;
};

int main(int argc, char const *argv[])
{
    Base b;
    Derived d1(b);
    std::cout << d1.text() << std::endl;

    Derived d2(d1);
    std::cout << d2.text() << std::endl;
    return 0;
}