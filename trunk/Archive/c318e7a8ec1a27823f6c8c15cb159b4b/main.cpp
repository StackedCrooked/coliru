#include "Poco/Stopwatch.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>


template<typename T, template<typename> class HookPolicy>
class Proxy : HookPolicy<T>
{    
public:
    Proxy(T & p) : HookPolicy<T>(p), ptr(&p)  { }
    T* operator->() { return ptr; }
    
private:
    T * ptr;    
};


template<typename T, template<typename> class HookPolicy>
class Wrap
{
    typedef Proxy<T, HookPolicy> ProxyType;
    
public:
    template<typename ...Args>
    explicit Wrap(Args && ...inArgs) : mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    /**
     * Apply the "before" and "after" hooks around a single method call.
     */
    ProxyType operator->() const { return ProxyType(mObject); }
    
    /**
     * The execute_around method can be used if you want to apply the
     * "before" and "after" hooks around a group of statements.
     * 
     * This makes sense for e.g. coordinated mutex locking.
     * 
     * Usage example:
     *   Wrap<int, policies::MutexLock> wrap(1);
     *   wrap.execute_around([](int & n) { std::cout << ++n << std::endl; });
     */
    template<typename Fun>
    void execute_around(const Fun & fun) const
    {
        ProxyType scoped_proxy(mObject);
        fun(mObject);
    }
    
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


int main()
{
    using policies::Group;
    using policies::Timer;
    using policies::MutexLock; 
    using policies::Inspect;
    
    typedef Wrap<std::string, Group<Timer, MutexLock, Inspect>::Rebind> String;
    
    String wrap("test");    
    
    std::cout << "\nSimple method call." << std::endl;
    std::cout << "Size: " << wrap->size() << std::endl;
    
    
    std::cout << "===\nTest execute_around(...)" << std::endl;
    wrap.execute_around([](std::string &s) {
        std::cout << "Start reversing the string...";
        std::reverse(s.begin(), s.end());
        std::cout << " Reverse complete!" << std::endl;
    });
    
    std::cout << "===\nTest Wrap<int>" << std::endl;
    Wrap<int, policies::Inspect> wrap_int(1);
    wrap_int.execute_around([](int & n) { std::cout << n++ << std::endl; });
}


// User override
namespace policies {


template<> std::mutex & GetMutex<std::string>(const std::string & )
{
    static std::mutex m;
    return m;
}


} // namespace policies
