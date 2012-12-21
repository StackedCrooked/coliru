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
struct Wrap
{
    template<typename ...Args>
    explicit Wrap(Args && ...inArgs) : mObject(std::forward<Args>(inArgs)...) { }
    
    Proxy<T, HookPolicy> operator->() const { return lock(); }    
    
    Proxy<T, HookPolicy> lock() const { return Proxy<T, HookPolicy>(&mObject); }
    
private:
    friend std::ostream& operator<<(std::ostream & os, Wrap<T, HookPolicy> & wrap)
    {
        auto lock = wrap.lock();
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
    using policies::Group;
    using policies::Timer;
    using policies::MutexLock; 
    using policies::Inspect;
    
    typedef Wrap<std::string, Group<Timer, MutexLock, Inspect>::Rebind> String;
    
    String wrap_string("test");    
    
    std::cout << "\n1" << std::endl;
    {
        auto proxy = wrap_string.lock();
        std::string & s = *proxy;
        s += "def";
        std::cout << "I am inside the scope." << std::endl;
    }    
    
    std::cout << "\n2" << std::endl;
    std::cout << wrap_string << std::endl;
    
    std::cout << "\n3" << std::endl;
    wrap_string->clear();
}
