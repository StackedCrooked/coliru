#include <cassert>
#include <cstddef>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <memory>
#include <mutex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T>
struct DefaultHookerTraits
{
    static void before(T&) { TRACE };
    static void after(T&)  { TRACE };
    typedef T* Ptr;
    typedef const T* ConstPtr;
};


template<typename T>
struct HookerTraits : DefaultHookerTraits<T>
{
};


template<typename T>
class Hooker
{    
public:
    Hooker(const T & t = T()) : t(t)
    {
        HookerTraits<T>::before(t);
    }
 
    ~Hooker()
    {
        HookerTraits<T>::after(t);
    }
    
    typedef typename HookerTraits<T>::Ptr Ptr;
    ConstPtr operator->() const { return &t; }
    Ptr operator->() { return &t; } 
    
public:    
    Hooker(Hooker&&) = default;
    Hooker& operator=(Hooker&&) = default;
    
    Hooker(const Hooker&) = delete;
    Hooker& operator=(const Hooker&) = delete;   
    
private:
    T & t;
};


template<class T>
class Proxy
{
public:
    explicit Proxy(const T & t = T()): obj(&t) { }
    
    Hooker<T> operator->() const
    {
        return Hooker<T>(*obj);
    }
    
private:
    T * obj;
};


struct Item
{
    void foo() const { TRACE }
    void bar() const { TRACE }
};


template<>
struct HookerTraits<Item>
{
    static void before(Item&) { std::cout << "..." << std::endl; }
    static void after(Item&) {}    
    typedef Item* Ptr;
};


template<typename T>
struct WithMutex
{
    WithMutex(const T & t = T()) : t(&t) {}
    typename HookerTraits<T>::ConstPtr operator->() const { return t; }
    typename HookerTraits<T>::Ptr operator->() { return t; } 
    
    mutable std::mutex mtx;
    T * t;
};


template<typename T>
struct HookerTraits< WithMutex<T> >
{
    static void before(WithMutex<T> & wm) { std::cout << "lock"   << std::endl; wm.mtx.lock(); }
    static void after(WithMutex<T> & wm)  { std::cout << "unlock" << std::endl; wm.mtx.unlock(); }
    
    typedef WithMutex<T> Ptr; // not really a pointer!
};


int main()
{
    Proxy<Item> item;
    item->foo();
    item->bar();
    
    Proxy<WithMutex<std::string>> safe;
    safe->empty();
}