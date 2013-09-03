class Base
{
public:
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    Derived(int p) : m(p) {}
    int m;
};

#include <memory>

int main()
{
    auto sder = std::make_shared<Derived>(42);
    auto rder = new              Derived (42);
    
    std::shared_ptr<Base> sbas = sder;
                    Base* rbas = rder;
    
    std::shared_ptr<Derived> sder2 = std::static_pointer_cast<Derived>(sbas);
                    Derived* rder2 = static_cast<Derived*>(rbas);
}
