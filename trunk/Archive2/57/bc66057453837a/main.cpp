#include <iostream>
#include <typeinfo>

struct Base1 {
    virtual ~Base1() {}
};
struct Base2 {
    virtual ~Base2() {}
};

struct OtherBase {
    virtual ~OtherBase() {}
};

struct MyClass 
    : Base1, Base2
{};

struct Derived
    : OtherBase
    , MyClass
{};

template<class T>
void recover(void* ptr, std::type_info const& ti) {
    if (ti==typeid(T)) {
        T* p=static_cast<T*>(ptr);
        std::cout << "OK: " << p << std::endl;
    } else 
        std::cout << "not OK" << std::endl;
}

int main() {
    MyClass* p=new Derived();
    
    std::cout << static_cast<void*>(p) << std::endl;    
    std::cout << static_cast<void*>(static_cast<Base1*>(p)) << std::endl;
    std::cout << static_cast<void*>(static_cast<Base2*>(p)) << std::endl;
    std::cout << static_cast<void*>(dynamic_cast<Derived*>(p)) << std::endl;
    std::cout << static_cast<void*>(dynamic_cast<OtherBase*>(p)) << std::endl;
    
    std::cout << dynamic_cast<void*>(p) << std::endl;
    
    void* vo=dynamic_cast<void*>(p);
    std::type_info const& ti=typeid(*p);
    
    recover<Base2>(vo, ti);
    recover<Derived>(vo, ti);
    
}
    
