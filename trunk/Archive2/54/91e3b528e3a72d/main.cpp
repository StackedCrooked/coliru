#include <memory>
#include <functional>
#include <iostream>

struct Base
{
    virtual void function() const noexcept = 0;
};
struct Derived : public Base
{
    inline virtual void function() const noexcept override
    {
        std::cout << "Derived" << std::endl;    
    }
};

int main()
{
    std::shared_ptr<Base> base = std::make_shared<Derived>();
    auto f = std::bind(&Base::function, base);
    f();
}