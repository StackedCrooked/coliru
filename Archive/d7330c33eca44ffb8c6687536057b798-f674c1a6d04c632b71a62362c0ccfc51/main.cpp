#include <functional>
#include <cstdio>
#include <vector>

class Base {
    public:
        Base() : ms_int(5) {}
        Base(int _ms_int) : ms_int(_ms_int) { }
        virtual int get_int() { return ms_int; };
    
    public:
        const int ms_int = 5;
};

class Derived : public Base {
    public:
        Derived() : Base(25) {}
};

int main()
{
    Base b;
    Derived d;
    printf("base: %d\n", b.get_int());
    printf("derived: %d\n", d.get_int());
    
    return 0;
}
