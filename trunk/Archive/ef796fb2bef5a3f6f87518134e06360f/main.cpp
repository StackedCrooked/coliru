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
struct HookerTraits
{
    static void before(T&) { TRACE };
    static void after(T&)  { TRACE };
};


template<typename T>
class Hooker
{    
public:
    Hooker(T & t) : t(t)
    {
        HookerTraits<T>::before(t);
    }
 
    ~Hooker()
    {
        HookerTraits<T>::after(t);
    }
    
    const T * operator->() const { return &t; }
    T * operator->() { return &t; } 
    
public:    
    Hooker(Hooker&&) = default;
    Hooker& operator=(Hooker&&) = default;
    
    Hooker(const Hooker&) = delete;
    Hooker& operator=(const Hooker&) = delete;   
    
private:
    T & t;
};


template<class T>
class Pointer
{
public:
    explicit Pointer(T * p = 0): p(p) { }
    
    Hooker<T> operator->() const
    {
        assert(p);
        return Hooker<T>(*p);
    }
    
private:
    T * p;
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
};


template<typename T>
struct WithMutex : T
{
    const T* operator->() const { return this; }
    T * operator->() { return this; } 
    
    mutable std::mutex mtx;
};


template<typename T>
struct HookerTraits< WithMutex<T> >
{
    static void before(WithMutex<T> & wm) { std::cout << "lock"   << std::endl; wm.mtx.lock(); }
    static void after(WithMutex<T> & wm)  { std::cout << "unlock" << std::endl; wm.mtx.unlock(); }
};


int main()
{
    Pointer<Item> item(new Item);
    item->foo();
    item->bar();
    
    Pointer<WithMutex<std::string>> safe(new std::string);
    safe->empty();
}