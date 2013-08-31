#include <iostream>
#include <mutex>
#include <string>


#define TRACE {std::cout << __PRETTY_FUNCTION__ << std::endl;}


template<typename T>
struct Wrap;


class Resource {
    Resource() {}
    friend struct Wrap<Resource>;
    
public:
    void access() { std::cout << "access" << std::endl; }    
};


template<typename T>
class Wrap {
    friend struct Locker;
    typedef std::mutex Mutex;
    typedef std::unique_lock<Mutex> ScopedLock;
    Mutex mtx_;
    T obj_;
    
public:
    template<typename ...Args>
    explicit Wrap(Args && ...args) : obj_(std::forward<Args>(args)...)
    {
        TRACE
    }
    
    class Locker : ScopedLock {
        T & obj_;
        
    public:        
        Locker(Wrap<T> & wrap) : ScopedLock(wrap.mtx_), obj_(wrap.obj_) { TRACE }        
        T & get() { return obj_; }
    };
    
    Locker lock() { return Locker(*this); }
};

typedef Wrap<Resource> SharedResource;

SharedResource & GetSharedResource()
{
    TRACE
    static SharedResource fSharedResource;
    return fSharedResource;
}

int main()
{
    {
        SharedResource::Locker lock = GetSharedResource().lock();
        Resource & theResource = lock.get();
        theResource.oi();
    }
    {
        SharedResource::Locker lock = GetSharedResource().lock();
        Resource & theResource = lock.get();
        theResource.oi();
    }
}
