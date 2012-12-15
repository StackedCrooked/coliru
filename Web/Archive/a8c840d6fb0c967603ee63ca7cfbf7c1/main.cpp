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

template<typename T> struct Hooker;

template<typename T> struct DefaultHookerTraits {
    void before() { TRACE };
    void after()  { TRACE };
    
    const Hooker<T> & get_hooker() const { return static_cast<Hooker<T>&>(*this); }
    Hooker<T> & get_hooker() { return static_cast<Hooker<T>&>(*this); }
    
    const T & get_value() const { return *get_hooker().t; }
    T & get_value() { return *get_hooker().t; }
};

template<typename T> struct HookerTraits : DefaultHookerTraits<T> {};

template<typename T> struct Hooker : HookerTraits<T> {    
    Hooker(const T & t) : t(const_cast<T*>(&t)) { this->before(); } 
    ~Hooker() { this->after(); }
    
    const T * operator->() const { return t; }
    T * operator->() { return t; }
        
    Hooker(Hooker&&) = default;
    Hooker& operator=(Hooker&&) = default;
    
    Hooker(const Hooker&) = delete;
    Hooker& operator=(const Hooker&) = delete;   
    
    T * t;
};

template<class T> struct Proxy {
    template<typename ...Args>
    explicit Proxy(Args && ...args): t(std::forward<Args>(args)...) { }
    
    Hooker<T> operator->() const {
        return Hooker<T>(t);
    }    
    T t;
};

struct Item {
    void foo() const { TRACE }
    void bar() const { TRACE }
};

template<> struct HookerTraits<Item> : DefaultHookerTraits<Item> {
    void before() { std::cout << "SPECIAL BEFORE! (" << &get_value() << ")" << std::endl; }
};

template<> struct HookerTraits<std::string> : DefaultHookerTraits<std::string> {
    void before() { std::cout << "Before: " << get_value() << std::endl; }
    void after() { std::cout << "After: " << get_value() << std::endl; }
};

int main() {
    Proxy<Item> item;
    item->foo();
    
    std::cout << "\nWith std::string:" << std::endl;
    Proxy<std::string> s;
    
    std::cout << "\nPushing back a character: " << std::endl;
    s->push_back('a');
    
    std::cout << "\nClearing the string: " << std::endl;
    s->clear();
}