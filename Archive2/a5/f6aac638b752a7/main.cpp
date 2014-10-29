#include <iostream>

class Base {
public:
    Base() {}
    operator int() const { return getInt(); }
protected:
    virtual int getInt() const { return 0; }
};

class Derived1 : public Base {
public:
    Derived1() : Base() {}
protected:
    virtual int getInt() const override { return 1; }
};

class Derived2 : public Base {
public:
    Derived2() : Base() {}
protected:
    virtual int getInt() const override { return 2; }
};

Base* helper(const bool flag) {
    if (flag)
        return new Derived1();
    else
        return new Derived2();
}

int main()
{
    int one = *helper(true); // I expect "one" to be 1
    int two = *helper(false); // I expect "two" to be 2
    
    std::cout << one << two << std::endl;
}
