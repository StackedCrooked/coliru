#include <iostream>
#include <memory>

namespace {
    struct Base
    {
    };
    
    struct Derived : Base
    {
        Derived()  { std::cout << "Derived "  << this << '\n'; }
        ~Derived() { std::cout << "~Derived " << this << '\n'; }
    };
        
}

int main()
{
    {
        std::shared_ptr<Base> p1 = std::make_shared<Derived>();
    }
    
    {
        std::unique_ptr<Base> p2(new Derived);
    }
    
    {
        Base* p3 = new Derived;
        delete p3;
    }
}