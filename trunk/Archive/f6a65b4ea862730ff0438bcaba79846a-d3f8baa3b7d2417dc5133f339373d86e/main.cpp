#include <iostream>
#include <mutex>
#include <thread>


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }

private:
    friend class Locker<T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:
    Locker(const Locker<T>&) = delete;
    Locker& operator=(const Locker<T>&&) = delete;
    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
Locker<T> lock(Protected<T> & p)
{
    return Locker<T>(p);
}


struct Foo
{
    void bar()
    {
        std::cout << "Foo::bar" << std::endl;
    }
};


int main()
{
    Protected<Foo> foo;
    
    {
        Locker<Foo> lock(foo);
        lock->bar();
    }
    
    {
        lock(foo)->bar();
    }
    
}