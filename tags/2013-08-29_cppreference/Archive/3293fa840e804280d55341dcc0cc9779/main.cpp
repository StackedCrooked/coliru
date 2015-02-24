#include "Poco/Stopwatch.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>



template<typename T, template<typename> class HookPolicy>
struct Proxy : HookPolicy<T>
{
    Proxy(T & p) : HookPolicy<T>(p), ptr(&p)  { }    
    
    T* operator->() { return ptr; }
    
private:
    T * ptr;
};


template<typename T, template<typename> class HookPolicy>
struct Wrap
{
    template<typename ...Args>
    explicit Wrap(Args && ...inArgs) : mObject(std::forward<Args>(inArgs)...) { }
    
    /**
     * Apply the "before" and "after" hooks around a single method call.
     */
    Proxy<T, HookPolicy> operator->() const { return Proxy<T, HookPolicy>(mObject); }
    
private:    
    mutable T mObject;
};


namespace policies {


template<typename T>
struct Inspect
{
    Inspect(T & t) : ptr(&t) { std::cout << "Inspect before: " << *ptr << std::endl; }   
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
    MutexLock(T & t) : data(new Data(GetMutex<T>(t))) { }

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
    Timer(T &) : stopwatch(new Poco::Stopwatch) { stopwatch->start(); }    
    ~Timer() { std::cout << "Elapsed: " << stopwatch->elapsed() << " us" << std::endl; }
    
private:
    std::shared_ptr<Poco::Stopwatch> stopwatch;
};


template<template<typename> class ...Args>
struct Group
{
    template<typename T>
    struct Rebind : Args<T>... { Rebind(T & t) : Args<T>(t)... { } };
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
    
    // Define three hooks: Timer, Mutex and Inspector.
    typedef Wrap<std::string, Group<Timer, MutexLock, Inspect>::Rebind> String;
    
    String wrap("test");    
    
    std::cout << "Appending 'a': ";
    wrap->push_back('a');
    std::cout << std::endl;
        
    std::cout << "Clearing: ";
    wrap->clear();
    std::cout << std::endl;
}