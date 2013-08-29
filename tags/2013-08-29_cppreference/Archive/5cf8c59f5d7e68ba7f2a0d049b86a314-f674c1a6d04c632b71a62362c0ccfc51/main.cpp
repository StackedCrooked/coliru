#include <cstdio>

class Base {
    public:
        enum Type { BaseClass, Type1, Type2 };
        const Type m_type = BaseClass;
};

class Derived1 : public Base {
    public:
        const Type m_type = Type1;
};

class Derived2 : public Base {
    public:
        const Type m_type = Type2;
};


int main()
{
    Base b;
    Derived1 d;
    Derived2 e;
    
    printf("base: %d\n", b.m_type);
    printf("derived1: %d\n", d.m_type);
    printf("derived2: %d\n", e.m_type);
    
    return 0;
}
