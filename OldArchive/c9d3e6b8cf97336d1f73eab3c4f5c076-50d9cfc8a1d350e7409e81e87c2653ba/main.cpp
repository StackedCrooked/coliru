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
    
    Locker(Locker<T> && rhs) = default;
    
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
    
    Locker(Locker<const T> && rhs) = default;
    
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
    return Locker<T>(*this);
}


template<typename T>
Locker<const T> Protected<T>::operator->() const
{
    return Locker<T>(*this);
}

struct Foo
{
    void bar() { std::cout << "Foo::bar()" << std::endl; }
    void car() const { std::cout << "Foo::car() const" << std::endl; }
};

int main()
{
    Protected<Foo> foo;
    
    // Using Locker<T> for full access.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
        foo.car();
    }
    
    // Using Locker<const T> for const access
    {
        Locker<const Foo> locker(foo);
        const Foo & foo = locker.get();
        foo.car(); // can only call const methods
    }
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
    foo->car();
}

    