#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>
#include <typeinfo>
#include <cxxabi.h>


std::string Demangle(const char * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);

    if (st != 0)
    {
        switch (st)
        {
            case -1: throw std::runtime_error("A memory allocation failure occurred.");
            case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
            case -3: throw std::runtime_error("One of the arguments is invalid.");
            default: throw std::runtime_error("Unexpected demangle status");
        }
    }

    std::string result(p);
    free(p);
    return result;
}


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
        HookedPtr(const T & obj) : WrapPtr<T>(obj), HookPolicy<T>(&obj) { }
        
        MOVE_ONLY(HookedPtr);
    };
    
    HookedPtr obtain() const
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
    
    
template<typename CRT>
struct Trace
{
    Trace() : enabled(false)
    {
        log("constructor");
    }
    
    ~Trace()
    {
        log("destructor");
    }
    
    void log(const std::string & msg)
    {
        if (enabled)
        {
            std::cout << Demangle(typeid(CRT).name()) << ": " << msg << std::endl;
        }
    }
    
    bool enabled;
};

    
template<typename T>
class MutexLock : Trace<MutexLock<T>>
{    
public:
    MutexLock(const T * = 0) :
        mtx(std::make_shared<std::mutex>())
    {
        mtx->lock();
    }
    
    ~MutexLock()
    {
        mtx->unlock();
    }
    
    MOVE_ONLY(MutexLock);
    
private:
    std::shared_ptr<std::mutex> mtx;
};

#define NAME(T) Demangle(typeid(T).name())

template<typename T>
struct XML : Trace<XML<T>>
{
    XML(const T * = 0)
    {
        std::cout << "<" << NAME(T) << ">" << std::endl;
    }
    
    ~XML()
    {
        std::cout << "</" << NAME(T) << ">" << std::endl;
    }
};


template<typename T>
struct MyDecorator : XML<T>, XML<XML<T>>, MutexLock<T>
{
    MyDecorator(const T * t = 0) : XML<T>(t), MutexLock<T>(t) {}
};


struct String : std::string {};
    
    
int main()
{
    
    Proxy<String, MyDecorator> string;
    
    {
        auto str = string.get();
        std::cout << "Pushing back 'a', 'b' and 'c'" << std::endl;
        str->push_back('a');
        str->push_back('b');
        str->push_back('c');
    }
    
    std::cout << *string.lock() << std::endl;
    
    std::cout << "Clearing the string..." << std::endl;
    string->clear();
    
    std::cout << "Done." << std::endl;
}
