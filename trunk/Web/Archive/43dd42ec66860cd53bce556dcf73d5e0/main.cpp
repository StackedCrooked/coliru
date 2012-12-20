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
    template<typename ...Args>
    explicit Proxy(Args && ...inArgs) :
        Holder<T>(std::forward<Args>(inArgs)...)
    {
    }
    
    std::shared_ptr<T> operator->() const
    {
        this->before();
        return std::shared_ptr<T>
        (
            const_cast<T*>(&this->mObject),
            std::bind(&HookPolicy<T>::after, static_cast<const HookPolicy<T> *>(this), std::placeholders::_1)
        );
    }
    
    friend std::ostream& operator<<(std::ostream & os, const Proxy<T, HookPolicy> & t)
    {
        auto lock = t.operator->();
        return os << t.mObject;
    }
};


namespace Policies {
    
    
template<typename T>
struct MutexLock
{    
    void before(const T* = nullptr) const
    {
        std::cout << "lock the mutex" << std::endl;
        mtx.lock();
    }
    
    void after(const T* = nullptr)  const
    {
        std::cout << "unlock the mutex" << std::endl;
        mtx.unlock();
    }
    
    mutable std::mutex mtx;
};


} // namespace Policies


int main()
{
    Proxy<std::string, Policies::MutexLock> str;
    
    std::cout << "\nAppending abc:" << std::endl;
    str->push_back('a');
    str->push_back('b');
    str->push_back('c');
    
    std::cout << "\nPrinting the string:" << std::endl;
    std::cout << str << std::endl;
    
    std::cout << "\nClearing the string:" << std::endl;
    str->clear();
}
