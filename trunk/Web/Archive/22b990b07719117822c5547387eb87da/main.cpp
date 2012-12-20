#include "Poco/Stopwatch.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>



template<typename T, template<typename> class HookPolicy>
struct Proxy : HookPolicy<T>
{
    Proxy(T * p) : HookPolicy<T>(p), ptr(p)  { }    
    T* operator->() { return get(); }    
    T& operator*()  { return *get(); }
    T* get() { return ptr; }

private:
    T * ptr;
};


template<typename T, template<typename> class HookPolicy>
struct Hookable
{
    template<typename ...Args>
    explicit Hookable(Args && ...inArgs) : mObject(std::forward<Args>(inArgs)...) { }
    
    typedef Proxy<T, HookPolicy> HookedProxy;
    
    HookedProxy operator->() const { return lock(); }    
    HookedProxy lock() const { return Proxy<T, HookPolicy>(&mObject); }
    
private:
    friend std::ostream& operator<<(std::ostream & os, Hookable<T, HookPolicy> & prot)
    {
        auto lock = prot.lock();
        return os << *lock.get() << std::endl;
    }
    
    mutable T mObject;
};


namespace policies {

template<typename T>
struct Inspect
{
    Inspect(T * p) : ptr(p) { std::cout << "Inspect before: " << *ptr << std::endl; }   
    ~Inspect() { std::cout << "Inspect after: " << *ptr << std::endl; }
    
private:
    T * ptr;
};


template<typename T>
std::mutex & GetMutex(const T & t)
{
    return t.get_mutex();
}


template<typename T>
struct MutexLock
{
    MutexLock(T * p) : data(new Data(GetMutex<T>(*p))) { }

private:    
    struct Data
    {
        Data(std::mutex & m) : mutex(m), lock(mutex) {}
        std::mutex & mutex;
        std::unique_lock<std::mutex> lock;
    };
    std::shared_ptr<Data> data;
};



template<typename T>
struct Timer
{
    Timer(T * = nullptr) : stopwatch(new Poco::Stopwatch) { stopwatch->start(); }    
    ~Timer() { std::cout << "Elapsed: " << stopwatch->elapsed() << " us" << std::endl; }
    
private:
    std::shared_ptr<Poco::Stopwatch> stopwatch;
};


template<template<typename> class ...Args>
struct Group
{
    template<typename T>
    struct Rebind : Args<T>... { Rebind(T * p) : Args<T>(p)... { } };
};


} // namespace policies



// User override
namespace policies {


template<> std::mutex & GetMutex<std::string>(const std::string & )
{
    static std::mutex m;
    return m;
}


} // namespace policies



int main()
{
    using namespace policies;
    
    Hookable<std::string, Group<Timer, MutexLock, Inspect>::Rebind> str("test");
    
    std::cout << "\n1" << std::endl;
    {
        auto proxy = str.lock();
        std::string & s = *proxy;
        s += "def";
        std::cout << "I am inside the scope." << std::endl;
    }    
    
    std::cout << "\n2" << std::endl;
    std::cout << str << std::endl;
    
    std::cout << "\n3" << std::endl;
    str->clear();
}
