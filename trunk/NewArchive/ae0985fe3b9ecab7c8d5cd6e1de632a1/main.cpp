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
class Proxy : private Holder<T>, private HookPolicy<T>
{    
public:
    typedef Proxy<T, HookPolicy> ThisType;
    
    template<typename ...Args>
    explicit Proxy(Args && ...inArgs) :
        Holder<T>(std::forward<Args>(inArgs)...)
    {
    }
    
    struct Wrap
    {
        Wrap(const ThisType & p) : ptr(&const_cast<ThisType&>(p)) { ptr->hookPolicy().before(); }
        ~Wrap() { ptr->after(); }
        const T * operator->() const { return &ptr->mObject; }
        T * operator->() { return &ptr->mObject; }
        ThisType * ptr;
    };
    
    Wrap lock() const
    {
        this->before();
        return Wrap(*this);
    }
    
    Wrap operator->() const
    {
        return lock();
    }
    
    friend std::ostream& operator<<(std::ostream & os, const Proxy<T, HookPolicy> & t)
    {
        auto lock = t.operator->();
        return os << t.mObject;
    }
    
private:
    const HookPolicy<T> & hookPolicy() const { return static_cast<HookPolicy<T>&>(*this); }
    HookPolicy<T> & hookPolicy() { return static_cast<HookPolicy<T>&>(*this); }
};


namespace Policies {
    
    
template<typename T>
struct MutexLock
{    
    void before(const T* = nullptr) const
    {
        std::cout << "[lock]" << std::endl;
        mtx.lock();
    }
    
    void after(const T* = nullptr)  const
    {
        std::cout << "[unlock]" << std::endl;
        mtx.unlock();
    }
    
    mutable std::mutex mtx;
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
