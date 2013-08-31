#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T>
struct Holder
{
    template<typename ...Args>
    explicit Holder(Args && ...inArgs) :
        mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    T mObject;
};


template<typename T>
class WrapPtr
{    
public:
    WrapPtr(const T & t) : obj(&const_cast<T&>(t))
    {
    }
    
    const T& operator*() const { return *obj; }
    T& operator*() { return *obj; }
    
    const T * operator->() const { return obj; }
    T * operator->() { return obj; }
    
private:
    T * obj;
};


template<typename T, template<typename> class HookPolicy>
class Proxy;


    
    
#define MOVE_ONLY(Class) \
    Class(Class&&) = default; \
    Class& operator=(Class&&) = default; \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete
    
    

template<typename T, template<typename> class HookPolicy>
class Proxy : private Holder<T>
{    
public:
    typedef Proxy<T, HookPolicy> ThisType;
    
    template<typename ...Args>
    explicit Proxy(Args && ...inArgs) :
        Holder<T>(std::forward<Args>(inArgs)...)
    {
    }
    
    struct Wrap : WrapPtr<T>, HookPolicy<T>
    {
        Wrap(const T & t) : WrapPtr<T>(t), HookPolicy<T>(t) {}
        ~Wrap() {}
        
        MOVE_ONLY(Wrap);
    };
    
    Wrap lock() const
    {
        return Wrap(this->mObject);
    }
    
    Wrap operator->() const
    {
        return lock();
    }
    
    friend std::ostream& operator<<(std::ostream & os, const Proxy<T, HookPolicy> & t)
    {
        auto l = t.lock();
        return os << *l;
    }
};


namespace Policies {
    
template<typename T>
class MutexLock
{    
public:
    MutexLock(const T &) :
        mtx(std::make_shared<std::mutex>())
    {
        std::cout << "[lock]" << std::endl;
        mtx->lock();
    }
    
    ~MutexLock()
    {
        mtx->unlock();
        std::cout << "[unlock]" << std::endl;
    }
    
    MOVE_ONLY(MutexLock);
    
private:
    std::shared_ptr<std::mutex> mtx;
};


} // namespace Policies


int main()
{
    Proxy<std::string, Policies::MutexLock> string;
    
    {
        auto str = string.lock();
        str->push_back('a');
        str->push_back('b');
        str->push_back('c');
        std::cout << "Pushed them back alright!" << std::endl;
    }
    
    std::cout << "\nPrinting the string:" << std::endl;
    std::cout << string << std::endl;
    
    std::cout << "\nClearing the string:" << std::endl;
    string->clear();
}
