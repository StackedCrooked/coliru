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


template<typename T, class HookPolicy>
class Protected;


template<typename T, class HookPolicy>
class Protected : private WrapObj<T>
{    
public:
    template<typename ...Args>
    explicit Protected(Args && ...inArgs) :
        WrapObj<T>(std::forward<Args>(inArgs)...)
    {
    }
    
    class HookedPtr : public WrapPtr<T>, private HookPolicy
    {
    public:
        HookedPtr(const T & obj) : WrapPtr<T>(obj), HookPolicy() { }
        
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
    
    friend std::ostream& operator<<(std::ostream & os, const Protected<T, HookPolicy> & t)
    {
        auto l = t.lock();
        return os << *l;
    }
};

    
class MutexLock
{    
public:
    MutexLock() : mtx(std::make_shared<std::mutex>())
    {
        std::cout << "<lock>" << std::endl;
        mtx->lock();
    }
    
    ~MutexLock()
    {
        mtx->unlock();
        std::cout << "</lock>" << std::endl;
    }
    
    MOVE_ONLY(MutexLock);
    
private:
    std::shared_ptr<std::mutex> mtx;
};


struct Log
{
    Log() { std::cout << "LOG: constructor" << std::endl; }
    ~Log() { std::cout << "LOG: destructor" << std::endl; }
};


struct Underline
{
    Underline() { std::cout << "\n--- The Beginning ---" << std::endl; }
    ~Underline() { std::cout << "\n--- The End ---" << std::endl; }
};

#define GEN_POLICY(NAME) \
    struct NAME { \
        NAME() { std::cout << "<" << #NAME << ">" << std::endl; } \
        ~NAME() { std::cout << "</" << #NAME << ">" << std::endl; } \
    }
    
    
// Generate hook policies for testing purposes.
GEN_POLICY(A);
GEN_POLICY(B);
GEN_POLICY(C);
GEN_POLICY(D);


int main()
{
    // Chain a number of "hooks"
    Protected<std::string, std::tuple<MutexLock, A, B, C, D> > string;
    
    std::cout << "Before scope." << std::endl;
    {
        auto scoped = string.lock();
        scoped->push_back('d');        
        scoped->push_back('e');
        scoped->push_back('f');
    }
    std::cout << "After scope." << std::endl;
    
    std::cout << string << std::endl;    
    
    string->resize(2);
    
    std::cout << string << std::endl;    
}
