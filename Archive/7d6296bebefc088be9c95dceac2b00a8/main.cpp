#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>



template<typename T, template<typename> class HookPolicy>
struct Proxy : HookPolicy<T>
{
public:
    Proxy(T * p) : HookPolicy<T>(p), ptr(p)  { }
    
    const T * operator->() const { return ptr; }
    T * operator->() { return ptr; }
    
    const T * get() const { return ptr; }    
    T * get() { return ptr; }
    
    const T & ref() const { return *this->ptr; }    
    T & ref() { return *this->ptr; }
    
private:
    T * ptr;
};


template<typename T, template<typename> class HookPolicy>
class Protected
{    
public:
    template<typename ...Args>
    explicit Protected(Args && ...inArgs) :
        mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    Proxy<T, HookPolicy> operator->()
    {
        return lock();
    }
    
    Proxy<const T, HookPolicy> operator->() const
    {
        return lock();
    }
    
    Proxy<T, HookPolicy> lock()
    {
        return Proxy<T, HookPolicy>(&mObject);
    }
    
    Proxy<const T, HookPolicy> lock() const
    {
        return Proxy<const T, HookPolicy>(&mObject);
    }
    
private:
    friend std::ostream& operator<<(std::ostream & os, const Protected<T, HookPolicy> & prot)
    {
        auto lock = prot.lock();
        return os << lock.ref() << std::endl;
    }
    
    T mObject;
};


template<typename T>
class Policy
{
public:
    Policy(T * p) : ptr(p) {}
    
protected:
    const T * get_ptr() const { return ptr; }    
    T * get_ptr() { return ptr; }
    
private:
    T * ptr;
};


template<typename T>
struct GreetPolicy : Policy<T>
{
    GreetPolicy(T * p) : Policy<T>(p)
    {
        std::cout << "Hello " << *this->get_ptr() << std::endl;
    }
    
    ~GreetPolicy()
    {
        std::cout << "Goodbye " << *this->get_ptr() << std::endl;
    }
};


#define GEN_POLICY(NAME) \
    template<typename T> \
    struct NAME { \
        NAME(T * = 0) { std::cout << "BEGIN " << #NAME << "" << std::endl; } \
        ~NAME() { std::cout << "END " << #NAME << "" << std::endl; } \
    }
    
    
// Generate hook policies for testing purposes.
GEN_POLICY(A);
GEN_POLICY(B);
GEN_POLICY(C);


template<template<typename> class A, template<typename> class B>
struct CombinePolicies
{
    template<typename T>
    struct rebind : A<T>, B<T>
    {
        rebind(T * p) : A<T>(p), B<T>(p) {}
    };
};


int main()
{
    // Chain a number of "hooks"
    Protected<std::string, CombinePolicies<A, B>::rebind> s("test");
    
    std::cout << "\n1" << std::endl;
    {
        auto scoped = s.lock();
        scoped->push_back('d');
        scoped->push_back('e');
        scoped->push_back('f');
        std::cout << "I am inside the scope." << std::endl;
    }    
    
    std::cout << "\n2" << std::endl;
    std::cout << s << std::endl;
    
    std::cout << "\n3" << std::endl;
    s->clear();
}
