#include <cstdio>
#include <vector>

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
    std::vector<Base*> list;
    
    list.push_back(new Base());
    list.push_back(new Derived1());
    list.push_back(new Derived2());
    
    for(size_t i=0; i<list.size(); i++) {
        printf("class: %d\n", list[i]->m_type);
    }
    
    return 0;
}
