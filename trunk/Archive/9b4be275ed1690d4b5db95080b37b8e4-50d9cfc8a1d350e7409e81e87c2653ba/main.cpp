#include <iostream>
#include <mutex>
#include <memory>

template<typename>
struct Locker;

template<typename T>
struct Monitor
{
    template<typename ...Args>
    Monitor(Args && ...args) :
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
    Locker(Monitor<T> & p) :
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
Locker<T> Monitor<T>::operator->()
{
    return Locker<T>(const_cast<Monitor<T>&>(*this));
}

struct Foo
{
    void bar() { std::cout << "Foo::bar()" << std::endl; }
};

int main()
{
    auto fooPtr = std::make_shared<Foo>();
    
    Monitor<std::weak_ptr<Foo>> foo(fooPtr);
    
    if (std::shared_ptr<Foo> f = foo->lock())
    {
        f->bar();
    }
}

    