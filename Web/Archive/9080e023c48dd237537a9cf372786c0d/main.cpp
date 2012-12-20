#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

    
#define MOVE_ONLY(Class) \
        Class(Class&&) = default; \
        Class& operator=(Class&&) = default; \
        Class(const Class&) = delete; \
        Class& operator=(const Class&) = delete


template<typename T>
struct WrapObj
{
    template<typename ...Args>
    explicit WrapObj(Args && ...inArgs) :
        mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    const T & value() const { return mObject; }
    T & value() { return mObject; }
    
private:
    MOVE_ONLY(WrapObj);
    
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


template<typename T, template<typename> class HookPolicy>
class Proxy : private WrapObj<T>
{    
public:
    template<typename ...Args>
    explicit Proxy(Args && ...inArgs) :
        WrapObj<T>(std::forward<Args>(inArgs)...)
    {
    }
    
    class HookedPtr : public WrapPtr<T>, private HookPolicy<T>
    {
    public:
        HookedPtr(const T & obj) : WrapPtr<T>(obj), HookPolicy<T>(obj) { }
        
        MOVE_ONLY(HookedPtr);
    };
    
    HookedPtr lock() const
    {
        return HookedPtr(this->value());
    }
    
    HookedPtr operator->() const
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
