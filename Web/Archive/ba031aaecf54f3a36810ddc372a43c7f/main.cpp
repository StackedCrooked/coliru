#include <cstddef>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <string>
#include <memory>
#include <mutex>


struct ScopedLock : std::unique_ptr<std::mutex>
{
    ScopedLock(std::mutex & mtx) : mtx(mtx)
    {
        std::cout << "ScopedLock" << std::endl;
    }
    
    ~ScopedLock()
    {
        std::cout << "~ScopedLock" << std::endl;                
    }
    
    std::mutex & mtx;
};


template<class T>
class Wrapper
{
public:
    const T * operator -> () const
    {
        return &obj;
    }

    T * operator -> ()
    {
        ScopedLock lock(mtx);
        std::unique_ptr<std::condition_variable, decltype(&_notify)> ptr(&cond, &_notify);
        return &obj;
    }

private:
    static void _notify(std::condition_variable * c)
    {
        std::cout << "before notify" << std::endl;
        c->notify_one();
        std::cout << "after notify" << std::endl;
    }

    mutable std::condition_variable cond;
    mutable std::mutex mtx;
    T obj;
};


struct Foo
{
    void cfoo() const { std::cout << "cfoo" << std::endl; }
    
    void foo() { std::cout << "foo" << std::endl; }
};



int main()
{
    Wrapper<Foo> wrap;
    {
        std::cout << "before foo" << std::endl;
        wrap->foo();
        std::cout << "after foo" << std::endl;
    }
    {
        std::cout << "before cfoo" << std::endl;
        wrap->cfoo();
        std::cout << "after cfoo" << std::endl;
    }
}