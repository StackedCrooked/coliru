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

template<typename T> struct DefaultHookerTraits {
    static void before(T&) { TRACE };
    static void after(T&)  { TRACE };
};

template<typename T> struct HookerTraits : DefaultHookerTraits<T> {};

template<typename T> struct Hooker {    
    Hooker(T & t) : t(t) { HookerTraits<T>::before(t); } 
    ~Hooker() { HookerTraits<T>::after(t); }
    
    const T * operator->() const { return &t; }                
    T * operator->() { return &t; }     
        
    Hooker(Hooker&&) = default;
    Hooker& operator=(Hooker&&) = default;
    
    Hooker(const Hooker&) = delete;
    Hooker& operator=(const Hooker&) = delete;   
    
    T & t;
};

template<class T> struct Pointer {
    explicit Pointer(T* p = 0): p(p) { }
    Hooker<T> operator->() const {
        assert(p);
        return Hooker<T>(*p);
    }
    
    T * p;
};

struct Item {
    void foo() const { TRACE }
    void bar() const { TRACE }
};

template<> struct HookerTraits<Item> : DefaultHookerTraits<Item> {
    static void before(Item&) { std::cout << "SPECIAL BEFORE!" << std::endl; }
};

int main() {
    Pointer<Item> item(new Item);
    item->foo();
}