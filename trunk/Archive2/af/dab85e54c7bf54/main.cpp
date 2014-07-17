#include <iostream>
#include <functional>
#include <utility>


#define TRACE() std::cout << __FILE__ << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;


template<typename T>
struct Lazy
{
    template<typename F>
    Lazy(F&& f) : t(), f(std::forward<F>(f)) { TRACE() }
    
    

    T* operator->()
    {
        TRACE()
        if (f)
        {
            t = f();
        }
        return &t;
    }
    
    const T& get() const { return t; }
    T& get() { return t; }

private:
    T t;
    std::function<T()> f;
};


template<typename T>
struct Lazy<T&>
{
    template<typename F>
    Lazy(F&& f, typename std::enable_if<std::is_same<decltype(f()), T&>::value>::type* = 0) : t(), f_(std::forward<F>(f)) { TRACE(); }
    
    template<typename F>
    Lazy(F&& f, typename std::enable_if<std::is_same<decltype(f()), T*>::value>::type* = 0) : t(), f_([f]() -> T& { return *f(); }) { TRACE(); }
    
    
    
    T* operator->()
    {
        TRACE()
        if (f_)
        {
            t = &f_();
        }
        return t;
    }
    
    const T& get() const { return *t; }
    T& get() { return *t; }
    
private:
    T* t;
    std::function<T&()> f_;
};


struct Session
{
    Session()   { TRACE() }
    void test() { TRACE() }
    
    static Session& Get()
    {
        static Session fSession;
        return fSession;
    }
};


int main()
{
    TRACE()
    Lazy<Session&> session([]() -> Session& { return Session::Get(); });
    session->test();
    
    Lazy<Session&> session2([] { return new Session(); });
}
