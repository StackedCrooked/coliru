#include <functional>
#include <cstdio>
#include <vector>

class Base {
    public:
        enum Type { BASE, DERIVED1, DERIVED2 };
        Base() : type(BASE) {}
        Base(Type t) : type(t) {}
        const Type get_type() { return type; };
    
    public:
        const Type type;
};

class Derived1 : public Base {
    public:
        Derived1() : Base(DERIVED1) {}
};

class Derived2 : public Base {
    public:
        Derived2() : Base(DERIVED2) {}
};


int main()
{
    std::vector<Base*> list;
    
    list.push_back(new Base());
    list.push_back(new Derived1());
    list.push_back(new Derived2());
    
    for(size_t i=0; i<list.size(); i++) {
        printf("class: %d\n", list[i]->get_type());
    }
    
    return 0;
}
