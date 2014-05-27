#include <iostream>
#include <vector>
#include <memory>

template<class Base>
struct FooDispatcher {
    template<class Derived, class Func>
    bool Add(Func func) {
        auto lambda = [=](std::shared_ptr<Base>& ptr)->void {
            std::shared_ptr<Derived> d = std::dynamic_pointer_cast<Derived>(ptr);
            if (d)
                func(std::move(d));
        };
        functions.push_back(lambda);
        return true;
    }
    void dispatch(std::shared_ptr<Base>& ptr)
    {
        for(auto& func : functions)
            func(ptr);
    }
private:
    std::vector<std::function<void(std::shared_ptr<Base>&)>> functions;
};


struct Base 
{ 
    typedef std::shared_ptr < Base > Ptr;
    virtual ~Base () {}
};

struct Derived1 : public Base 
{
    typedef std::shared_ptr < Derived1 > Ptr;    
};

struct Derived2 : public Base
{
    typedef std::shared_ptr < Derived2 > Ptr;    
};


void fooImpl1( Derived1::Ptr ptr )
{
   std::cout << "Came to fooImpl(Derived1::Ptr).\n";
}

void fooImpl2( Derived2::Ptr ptr )
{
   std::cout << "Came to fooImpl(Derived2::Ptr).\n";
}

// Test...    
int main()
{
    FooDispatcher<Base> dispatch;
    dispatch.Add<Derived1>(fooImpl1);
    dispatch.Add<Derived2>(fooImpl2);
    
    Base::Ptr ptr(new Derived1);
    dispatch.dispatch(ptr);

    ptr = Base::Ptr(new Derived2);
    dispatch.dispatch(ptr);
}