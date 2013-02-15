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


template<typename T, template<typename> class HookPolicy>
class Proxy;


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
    
    HookPolicy<T> lock() const
    {
        return HookPolicy<T>(this->mObject);
    }
    
    HookPolicy<T> operator->() const
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
    MutexLock(const T & t) :
        mtx(std::make_shared<std::mutex>()),
        obj(&const_cast<T&>(t))
    {
        std::cout << "[lock]" << std::endl;
        mtx->lock();
    }
    
    MutexLock(MutexLock<T>&&) = default;
    MutexLock& operator=(MutexLock<T>&&) = default;
    
    MutexLock(const MutexLock<T>&) = delete;
    MutexLock& operator=(const MutexLock<T>&) = delete;
    
    ~MutexLock()
    {
        mtx->unlock();
        std::cout << "[unlock]" << std::endl;
    }
    
    const T& operator*() const { return *obj; }
    T& operator*() { return *obj; }
    
    const T * operator->() const { return obj; }
    T * operator->() { return obj; }
    
private:
    std::shared_ptr<std::mutex> mtx;
    T * obj;
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
