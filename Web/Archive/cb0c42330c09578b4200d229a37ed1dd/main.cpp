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
struct Proxy
{
    Proxy(T * t) : t(t)
    {
        t->before();
    }
    
    ~Proxy()
    {
        t->after();
    }
    
    const T * operator->() const { return t; }
    
    T * operator->() { return t; }
    
    T * t;
};


template<class T>
class Pointer
{
public:
    explicit Pointer(T* p = 0): p(p) { }
    
    Proxy<T> operator->() const
    {
        return Proxy<T>(p);
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