#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>


template<typename T>
class Proxy
{    
public:
    Proxy(T * p) : ptr(p)  { }
    
    const T& operator*() const { return *ptr; }
    T& operator*() { return *ptr; }
    
    const T * operator->() const { return ptr; }
    T * operator->() { return ptr; }
    
private:
    T * ptr;
};
    
template<typename T, typename HookPolicy>
class HookedProxy : public Proxy<T>, private HookPolicy
{
public:
    HookedProxy(T * p) : Proxy<T>(p), HookPolicy() { }
};


template<typename T, class HookPolicy>
class Protected
{    
public:
    template<typename ...Args>
    explicit Protected(Args && ...inArgs) :
        mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    HookedProxy<T, HookPolicy> operator->()
    {
        return HookedProxy<T, HookPolicy>(&mObject);
    }
    
    HookedProxy<const T, HookPolicy> operator->() const
    {
        return HookedProxy<const T, HookPolicy>(&mObject);
    }
    
private:
    friend std::ostream& operator<<(std::ostream & os, const Protected<T, HookPolicy> & t)
    {
        auto l = t.operator->();
        return os << *l;
    }
    
    T mObject;
};


#define GEN_POLICY(NAME) \
    struct NAME { \
        NAME() { std::cout << "BEGIN " << #NAME << "" << std::endl; } \
        ~NAME() { std::cout << "END " << #NAME << "" << std::endl; } \
    }
    
    
// Generate hook policies for testing purposes.
GEN_POLICY(A);
GEN_POLICY(B);
GEN_POLICY(C);


int main()
{
    // Chain a number of "hooks"
    Protected<std::string, std::tuple<A, B, C> > s;
    {
        auto scoped = s.operator->();
        scoped->push_back('d');        
        scoped->push_back('e');
        scoped->push_back('f');
    }    
    std::cout << s << std::endl;
    s->clear();
}
