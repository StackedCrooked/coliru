#include <iostream>
#include <mutex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename>
class Locker;


template<typename T>
class Monitor
{
public:
    template<typename ...Args>
    Monitor(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }    

private:
    friend class Locker<T>;
    friend class Locker<const T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
class Locker
{
public:
    Locker(Monitor<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
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
class Locker<const T>
{
public:
    Locker(const Monitor<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
    }
    
    Locker(Locker<const T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
    }
    
    const T& get() const { return obj_; }    
    const T* operator->() const { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    const T & obj_;
};

struct Foo
{
    void bar() { TRACE }
    void car() const { TRACE }
};

int main()
{
    Monitor<Foo> foo;
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
        foo.car();
    }
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<const Foo> locker(foo);
        const Foo & foo = locker.get();
        foo.car();
    }
}

    