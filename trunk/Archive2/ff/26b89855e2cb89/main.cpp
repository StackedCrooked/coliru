#include <memory>
#include <iostream>
#include <iomanip>

struct X
{ 
    virtual void foo() { std::cout << "X::foo()\n"; }
};

struct Y : X 
{ 
    virtual void foo() override { std::cout << "Y::foo()\n"; }
};

struct Z : Y
{
    virtual void foo() override { std::cout << "Y::foo()\n"; }
};

template<typename T, typename U>
std::unique_ptr<T> downcast_unique(std::unique_ptr<U> p)
{
    return std::unique_ptr<T>(dynamic_cast<T*>(p.release()));
}

template<typename T, typename U>
std::unique_ptr<T> checked_downcast_unique(std::unique_ptr<U>&& p)
{
    auto pT = dynamic_cast<T*>(p.get());
    if (pT == nullptr) { return std::unique_ptr<T>(); }
    
    p.release();
    
    return std::unique_ptr<T>(pT);
}

int main()
{
    std::unique_ptr<X> x(new Y());
    
    auto y = std::dynamic_pointer_cast<Y>(std::move(x));
    
    y->foo();
}
