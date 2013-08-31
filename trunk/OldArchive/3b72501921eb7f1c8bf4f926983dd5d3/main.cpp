#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T, template<typename> class HookPolicy>
class Proxy : private HookPolicy<T>
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
                                  std::bind(&HookPolicy<T>::after,
                                            static_cast<const HookPolicy<T> *>(this),
                                            std::placeholders::_1));
    }
    
    std::shared_ptr<T> operator->() const
    {
        return lock();
    }
    
    friend std::ostream& operator<<(std::ostream & os, const Proxy<T, HookPolicy> & t)
    {
        auto lock = t.operator->();
        return os << t.mObject;
    }
    
private:
    T mObject;
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
    
    if (auto str = string.lock())
    {
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
