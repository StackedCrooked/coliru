#include <cstddef>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <memory>
#include <mutex>


template<class T>
struct Pointer
{
    explicit Pointer(T * p = 0): p(p)
    {
    }

    std::shared_ptr<T> operator->() const
    {
        p->prefix();
        return std::shared_ptr<T>(p, std::mem_fn(&T::suffix));
    }
    
private:
    T * p;
};


struct Item
{
    void foo()
    {
        std::cout << "Item::foo()" << std::endl;
    }
    
    void bar()
    {
        std::cout << "Item::bar()" << std::endl;
    }
    
private:
    friend class Pointer<Item>;
    
    void prefix() { std::cout << "Item::prefix" << std::endl; }
    void suffix() { std::cout << "Item::suffix" << std::endl; }
};


int main()
{
    Pointer<Item> item;
    item->foo();
    item->bar();
}