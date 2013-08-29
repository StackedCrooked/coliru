#include <iostream>
#include <mutex>


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
    
    Locker<const T> operator->() const;
    Locker<T> operator->();

private:    
    friend class Locker<T>;
    friend class Locker<const T>;
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
        std::cout << "LOCK" << std::endl;
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
        std::cout << "MOVE LOCK" << std::endl;
    }        
    
    ~Locker()
    {
        std::cout << "UNLOCK\n" << std::endl;
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
struct Locker<const T>
{
    Locker(const Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK (const)" << std::endl;
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
        std::cout << "MOVE LOCK (const)" << std::endl;
    }        
    
    ~Locker()
    {
        std::cout << "UNLOCK (const)\n" << std::endl;
    }
    
    const T& get() const { return obj_; }    
    const T* operator->() const { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    const T & obj_;
};


template<typename T>
Locker<T> Protected<T>::operator->()
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


template<typename T>
Locker<const T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}

struct Foo
{
    void bar() { std::cout << "Foo::bar()" << std::endl; }
    void car() const { std::cout << "Foo::car() const" << std::endl; }
};

int main()
{
    Protected<Foo> foo;
    
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
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
    foo->car();
}

    