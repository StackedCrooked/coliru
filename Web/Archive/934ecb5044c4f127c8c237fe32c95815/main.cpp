#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>


template<typename T, class HookPolicy>
class Proxy : private HookPolicy
{    
public:
    template<typename ...Args>
    explicit Proxy(Args && ...inArgs) :
        mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    std::shared_ptr<T> lock() const
    {
        this->before();
        return std::shared_ptr<T>(const_cast<T*>(&mObject),
                                  [this](T*){ this->after(); });
    }
    
    std::shared_ptr<T> operator->() const
    {
        return lock();
    }
    
private:
    T mObject;
};


template<typename T, typename P>
std::ostream& operator<<(std::ostream & os, const Proxy<T, P> & t)
{
    return os << *t.lock() << std::endl;
}


namespace Policies {
    
    
struct MutexLock
{    
    void before() const
    {
        std::cout << "[lock]" << std::endl;
        mtx.lock();
    }
    
    void after()  const
    {
        std::cout << "[unlock]" << std::endl;
        mtx.unlock();
    }
    
    mutable std::mutex mtx;
};


} // namespace Policies


#define TRACE(statement) std::cout << "\nTRACE: " << #statement << std::endl; statement


int main()
{
    Proxy<std::string, Policies::MutexLock> string;
    
    if (auto str = string.lock())
    {
        TRACE(str->push_back('a'));
        TRACE(str->push_back('b'));
        TRACE(str->push_back('c'));
    }
    
    TRACE(std::cout << string << std::endl);
    TRACE(string->clear());
}
