#include <iostream>
#include <mutex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


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
    
    Locker<T> operator->() const;

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
        TRACE
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
        TRACE
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
Locker<T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


int main()
{
    struct Foo
    {
        void bar() { TRACE }
    };
    
    Protected<Foo> foo;
    foo->bar();
}

    