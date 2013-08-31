#include <cstdio>
#include <vector>

class Base {
    public:
        enum Type { BaseClass, Type1, Type2 };
        const Type m_type = BaseClass;
    
    virtual ~Base() {};
};

class Derived1 : public Base {
    public:
        const Type m_type = Type1;
    
    virtual ~Derived1() {};
};

class Derived2 : public Base {
    public:
        const Type m_type = Type2;
    
    virtual ~Derived2() {};
};


int main()
{
    std::vector<Base*> list;
    
    list.push_back(new Base());
    list.push_back(new Derived1());
    list.push_back(new Derived2());
    
    for(size_t i=0; i<list.size(); i++) {
        Base *ptr = list[i];
        
        if (dynamic_cast<Derived1*>(ptr))
            printf("%lu is derived1\n", i);
        else if (dynamic_cast<Derived2*>(ptr))
            printf("%lu is derived2\n", i);
        else
            printf("%lu is base\n", i);
    }
    
    return 0;
}
