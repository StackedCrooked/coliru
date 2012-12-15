#include <cstddef>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <memory>
#include <mutex>


#define OPEN(x) std::cout << "<" << #x << ">" << std::endl;
#define CLOSE(x) std::cout << "</" << #x << ">" << std::endl;
#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;
#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T>
class Hooker
{
    T * t;
    
public:
    Hooker(T * t) : t(t) { t->before(); }    
    
    ~Hooker() { t->after(); }
    
    // Enable move
    Hooker(Hooker&&) = default;
    Hooker& operator=(Hooker&&) = default;
    
    // Disable copy
    Hooker(const Hooker&) = delete;
    Hooker& operator=(const Hooker&) = delete;
    
    const T * operator->() const { return t; }            
    T * operator->() { return t; }
};


template<class T>
class Pointer
{
public:
    explicit Pointer(T* p = 0): p(p) { }
    
    Hooker<T> operator->() const
    {
        return Hooker<T>(p);
    }
    
private:
    T * p;
};


struct Item
{
    void foo() const { TRACE }
    void bar() const { TRACE }
    

    void before() { OPEN(Item) }
    void after()  { CLOSE(Item) }
};


int main()
{
    Pointer<Item> item;
    item->foo();
    item->bar();
}