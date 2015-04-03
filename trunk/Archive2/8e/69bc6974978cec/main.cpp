#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>



struct any
{
    
    struct placeholder 
    {
        virtual ~placeholder() =default;
        
    };
    
    template <typename TDerived, typename... Ts>
    struct concrete : public placeholder, public concrete<TDerived>, public concrete<Ts>...
    {
        concrete(TDerived* ptr)
            : concrete<TDerived>(ptr)
            , concrete<Ts>(static_cast<Ts*>(ptr))...
        {
        }
    
    };
    
    template <typename T>
    struct concrete<T>
    {   
        concrete(T* p)
            :ptr{p}
            {}
        T* Get()
        {
            return ptr;
        }
    private:
        T *ptr;
    };
    
    template <typename T, typename... Ts>
    static any create(T* value)
    {
        return {new concrete<T,Ts...>(value), {std::cref(typeid(T)),std::cref(typeid(Ts))...}} ;
    }
    
    
    template <typename T>
    T* get()
    {
        auto comparer = [&](std::reference_wrapper<const std::type_info> i)
        {
            return i.get() == typeid(T);
        };
        
        if (!find_if(infos,comparer))
            throw 42;
        
        concrete<T>* pConcrete = dynamic_cast<concrete<T>*>(holder);
        return pConcrete->Get();
    }
    
    ~any()
    {
        delete holder;
        holder = nullptr;
    }
    
private:
    placeholder* holder;
    std::vector<std::reference_wrapper<const std::type_info>> infos;
    
    template <typename TCont, typename TPred>
    bool find_if(TCont const& cont, TPred const& pred) const
    {
        return std::find_if(std::begin(infos), std::end(infos), pred) != std::end(cont);
    }
    
    template <typename T>
    any(T* h, std::vector<std::reference_wrapper<const std::type_info>> i)
        : holder{h}
        , infos{i}
    {
        
    }
    
    
};
struct base2
{
    virtual ~base2() =default;
    virtual void bar()
    {
        std::cout <<"base2::bar()"   <<std::endl;
    }
};

struct base
{
    virtual ~base() =default;
    
    virtual void foo() 
    {
            std::cout <<"base::foo()"   <<std::endl;
    }
};


struct derived : public base2, public base
{
    int i = 6;
    virtual void foo()
    {
        std::cout <<"derived::foo()"   <<std::endl;
    }
    virtual void bar()
    {
        std::cout <<"derived::bar()"   <<std::endl;
    }
};


struct not_related
{
    virtual void foo()
    {
        std::cout <<"not_related::foo()"   <<std::endl;
    }
    
};
int main()
{
    derived d;
    any a = any::create<derived,base,base2>(&d);
    
    auto pBase2 = a.get<base2>();
    auto pBase = a.get<base>();
    //auto pNot_related = a.get<not_related>();
    pBase2->bar();
    pBase->foo();
    
    
   
    
    
}