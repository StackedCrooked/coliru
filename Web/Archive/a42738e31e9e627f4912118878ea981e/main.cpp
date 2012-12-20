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






template<typename T>
struct Locker
{    
    void before(const T* = nullptr) const { mtx.lock(); }
    
    void after(const T* = nullptr)  const { mtx.unlock(); }
    
    mutable std::mutex mtx;
};


int main() {

    std::cout << "\nWith std::string:" << std::endl;
    Proxy<std::string, Locker> s;

    std::cout << "\nPushing back a character a." << std::endl;
    s->push_back('a');
    
    std::cout << s << std::endl;

    std::cout << "\nClearing the string: " << std::endl;
    s->clear();
}
