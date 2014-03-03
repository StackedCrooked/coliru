#include <iostream>
#include <vector>

enum TAG {
    A,B,C,
};


struct Storage 
{ 
    TAG tag;
    virtual ~Storage() { }
};


template<typename T>
struct Base : Storage
{
    void doit() { static_cast<T *>(this)->doit(); }
};


struct Derived : Base<Derived>
{
    Derived() : tag(B) { }
    void doit() { std::cout << "Hello Derived\n"; }
};

int main(void)
{ 
    Derived d{};
    std::vector<Storage *> s { &d } ;

    for (auto & e : s)
    {
        switch(e->tag) {
            case A: 
                std::cout << "A" << std::endl; 
                break;
            case B:
                std::cout << "B" << std::endl;
                break;
            case C: 
                std::cout << "C" << std::endl;
                break;
            default:
                std::cout << "?" << std::endl;
                    
        }
    }
}
