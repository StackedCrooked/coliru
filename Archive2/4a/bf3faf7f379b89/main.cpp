#include <iostream>
#include <memory>
#include <string>
#include <vector>


namespace A {
    struct Stuff {};    
    std::string to_string(const Stuff&) { return "A::Stuff"; }
}


namespace B {
    struct Crap {};    
    std::string to_string(const Crap&) { return "B::Crap"; }
}


struct TypeErased
{
    template<typename T>
    TypeErased(const T& t) : mImpl(new Impl<T>(t)) {}
    
    std::string toString() const { return mImpl->toString(); }
    
private:
    struct ImplBase
    {
        virtual ~ImplBase() {}        
        virtual std::string toString() const = 0;
    };
    
    template<typename T>
    struct Impl : ImplBase
    {
        Impl(const T& t) : t(t) {}
        std::string toString() const override
        {
            // ADL-lookup is only required at point of instantiation.
            return to_string(t); 
        }
        T t;
    };
    
    std::unique_ptr<ImplBase> mImpl;
};


int main()
{
    std::vector<TypeErased> TypeEraseds;
    TypeEraseds.push_back(A::Stuff{});
    TypeEraseds.push_back(B::Crap{});
    
    std::cout << TypeEraseds[0].toString() << '\n';
    std::cout << TypeEraseds[1].toString() << '\n';
}
