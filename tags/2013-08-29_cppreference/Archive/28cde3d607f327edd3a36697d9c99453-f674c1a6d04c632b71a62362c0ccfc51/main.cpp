#include <functional>
#include <cstdio>
#include <vector>

class Base {
    public:
        enum Type { BASE, DERIVED1, DERIVED2, DERIVED3 };
        Base() : type(BASE) {}
        Base(Type t) : type(t) {}
        const Type get_type() { return type; };
    
    public:
        const Type type;
};

class Derived : public Base {
    public:
        Derived() : Base(DERIVED1) {}
};

int main()
{
    Base b;
    Derived d;
    printf("base: %d\n", b.get_type() == Base::DERIVED1);
    printf("derived: %d\n", d.get_type() == Base::DERIVED1);
    
    return 0;
}
