#include "Poco/Stopwatch.h"
#include <algorithm>
#include <cstdlib>
#include <cxxabi.h>
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

std::string demangle(const char * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);

    if (st != 0)
    {
        switch (st)
        {
            case -1: throw std::runtime_error("A memory allocation failure occurred.");
            case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
            case -3: throw std::runtime_error("One of the arguments is invalid.");
            default: throw std::runtime_error("Unexpected demangle status");
        }
    }

    std::string result(p);
    free(p);
    return result;
}

template<typename T>
struct TextDecoration
{
    TextDecoration(T &) {  std::cout << "\n*** OPEN " << demangle(typeid(T).name()) << " ****" << std::endl; }   
    ~TextDecoration()   { std::cout << "*** CLOSE "    << demangle(typeid(T).name()) << " ****" << std::endl; }   
    
private:
    T * ptr;
};


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
    using policies::TextDecoration;
    using policies::Timer;
    using policies::MutexLock; 
    using policies::Inspect;
    
    // Define three hooks: TextDecoration, Timer, Mutex and Inspector.
    typedef Wrap<std::string, Group<TextDecoration, Timer, MutexLock, Inspect>::Rebind> String;
    
    String wrap("Hello ");
    wrap->push_back('a');
    wrap->push_back('b');
    wrap->push_back('c');
    wrap->pop_back();
    wrap->pop_back();
    wrap->pop_back();
    wrap->clear();
}
