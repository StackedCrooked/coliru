#include <functional>
#include <cstdio>
#include <vector>

class Base {
    public:
        int get_int() { return ms_int; };
    
    protected:
        const int ms_int = 5;
};

class Derived : public Base {
    protected:
        const int ms_int = 20;
};

int main()
{
    Base b;
    Derived d;
    
    printf("base: %d\n", b.get_int());
    printf("derived: %d\n", d.get_int());
    
    return 0;
}
