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
public:
    Proxy(T * p) : HookPolicy<T>(p), ptr(p)  { }
    
    T * operator->() { return ptr; }
    
    T * get() { return ptr; }
    
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
        return os << *lock.get() << std::endl;
    }
    
    T mObject;
};


namespace policies {


template<typename T>
struct Inspect
{
    Inspect(T * p) : ptr(p)
    {
        std::cout << "Inspect before: " << *ptr << std::endl;
    }
    
    ~Inspect()
    {
        std::cout << "Inspect after: " << *ptr << std::endl;
    }
    
    T * ptr;
};


template<typename T>
struct MutexLock
{
    MutexLock(T * p) : data(new Data(GetMutex(*p)))
    {
    }
    
    struct Data
    {
        Data(const std::mutex & m) : mutex(const_cast<std::mutex&>(m)), lock(mutex) {}
        std::mutex & mutex;
        std::unique_lock<std::mutex> lock;
    };
    std::shared_ptr<Data> data;
};



template<typename T>
struct Timer
{
    Timer(T * = nullptr) : stopwatch(new Poco::Stopwatch)
    {
        stopwatch->start();
    }
    
    ~Timer()
    {
        std::cout << "Elapsed: " << stopwatch->elapsed() << " us" << std::endl;
    }
    
    std::shared_ptr<Poco::Stopwatch> stopwatch;
};


template<template<typename> class ...Args>
struct Group
{
    template<typename T>
    struct Rebind : Args<T>...
    {
        Rebind(T * p) : Args<T>(p)...
        {
        }
    };
};


}


class Item : public std::string
{
    typedef std::mutex Mutex;
    typedef std::shared_ptr<Mutex> MutexPtr;
    
public:
    Item() : mMutexPtr(new Mutex) {}
    Item(const char * c) : std::string(c), mMutexPtr(new Mutex) {}
    
private:    
    friend const std::mutex & GetMutex(const Item & item)
    {
        return *item.mMutexPtr;
    }
    
    MutexPtr mMutexPtr;
};


int main()
{
    using namespace policies;
    
    Protected<Item, Group<Timer, MutexLock, Inspect>::Rebind> s("test");
    
    std::cout << "\n1" << std::endl;
    {
        auto scoped = s.lock();
        scoped->append("def");
        std::cout << "I am inside the scope." << std::endl;
    }    
    
    std::cout << "\n2" << std::endl;
    std::cout << s << std::endl;
    
    std::cout << "\n3" << std::endl;
    s->clear();
}
