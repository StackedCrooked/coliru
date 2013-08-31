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
struct MutexLock
{
    MutexLock(T * p) : data(new Data(GetMutex(*p))) { }

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


std::mutex & GetMutex(std::string & item)
{
    static std::mutex fMutex;
    return fMutex;
}    


int main()
{
    using namespace policies;
    
    Hookable<std::string, Group<Timer, MutexLock, Inspect>::Rebind> str("test");
    
    std::cout << "\n1" << std::endl;
    {
        auto scoped = str.lock();
        std::string & s = *str;
        s += "def";
        std::cout << "I am inside the scope." << std::endl;
    }    
    
    std::cout << "\n2" << std::endl;
    std::cout << str << std::endl;
    
    std::cout << "\n3" << std::endl;
    str->clear();
}
