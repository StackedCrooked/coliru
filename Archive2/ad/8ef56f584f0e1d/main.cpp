#include <iostream>
#include <mutex>
#include <functional>

class SimpleFunction
{
public:
    SimpleFunction() : thunk(0) {}
    SimpleFunction(SimpleFunction&& r) : thunk(r.thunk) { r.thunk = nullptr; }
    ~SimpleFunction() { delete thunk; }
    
    SimpleFunction(void (*func)())
        : thunk(new Func(func)) {}
    
    template<typename T>
    explicit SimpleFunction(T&& obj)
        : thunk(new ObjInst<T>(std::forward<T>(obj))) {}
    
    template<typename T, typename U>
    SimpleFunction(T&& obj, U member)
        : thunk(new ObjMemberInst<T,U>(std::forward<T>(obj), member)) {}
    
    template<typename T>
    explicit SimpleFunction(T* obj)
        : thunk(new ObjPtr<T>(obj)) {}
    
    template<typename T, typename U>
    SimpleFunction(T* obj, U member)
        : thunk(new ObjMemberPtr<T,U>(obj, member)) {}
    
    SimpleFunction& operator=(SimpleFunction const& r) = delete;
    SimpleFunction& operator=(SimpleFunction&& r)
    {
        if (&r != this)
        {
            thunk = r.thunk;
            r.thunk = 0;
        }
        return *this;
    }
    
    void invoke() { thunk->invoke(); }
    
private:
    struct Base
    {
        virtual ~Base() {}
        virtual void invoke() = 0;
    };
    
    template<typename T>
    struct ObjInst : public Base
    {
        T obj;
        
        template<typename V>
        ObjInst(V&& obj) : obj(std::forward<V>(obj)) {}
        void invoke() { obj(); }
    };
    
    template<typename T, typename U>
    struct ObjMemberInst : public Base
    {
        T obj;
        U member;
        
        template<typename V>
        ObjMemberInst(V&& obj, U member) : obj(std::forward<V>(obj)), member(member) {}
        void invoke() { (obj.*member)(); }
    };
    
    template<typename T>
    struct ObjPtr : public Base
    {
        T* obj;
        
        ObjPtr(T* obj) : obj(obj) {}
        void invoke() { (*obj)(); }
    };
    
    template<typename T, typename U>
    struct ObjMemberPtr : public Base
    {
        T* obj;
        U member;
        
        ObjMemberPtr(T* obj, U member) : obj(obj), member(member) {}
        void invoke() { (obj->*member)(); }
    };
    
    struct Func : public Base
    {
        void (*f)();
        
        Func(void (*f)()) : f(f) {}
        void invoke() { f(); }
    };
    
    Base *thunk;
};

std::mutex trickTheCompiler;
typedef std::unique_lock<std::mutex> ScopedLock;

struct Test
{
    void operator()() const
    {
        ScopedLock lock(trickTheCompiler);
    }
};

void freefunc()
{
    ScopedLock lock(trickTheCompiler);
}

int main()
{
    Test a;
    Test b;
    
    SimpleFunction sfa(a, &Test::operator());
    SimpleFunction sfb(&b, &Test::operator());
    SimpleFunction sff(freefunc);
    
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> Timestamp;
    typedef std::chrono::nanoseconds Duration;
    
    Timestamp st, en;
    
    for (auto r = 0; r < 10; ++r)
    {
        SimpleFunction sfas(a);
        SimpleFunction sfa(a, &Test::operator());
        SimpleFunction sfbs(&b);
        SimpleFunction sfb(&b, &Test::operator());
        SimpleFunction sff(freefunc);

        st = Clock::now();
        for (auto i = 0; i < 100000; ++i)
        {
            sfas.invoke();
            sfa.invoke();
            sfbs.invoke();
            sfb.invoke();
            sff.invoke();
        }
        en = Clock::now();
        
        std::cout << "       SimpleFunction " << std::chrono::duration_cast<Duration>(en - st).count() / 100000 << "ns each" << std::endl;

        std::function<void()> stdfa(a);
        std::function<void()> stdfb(std::bind(&Test::operator(), &a));
        std::function<void()> stdff(freefunc);

        st = Clock::now();
        for (auto i = 0; i < 100000; ++i)
        {
            stdfa();
            stdfa();
            stdfb();
            stdfb();
            stdff();
        }
        en = Clock::now();
        
        std::cout << "        std::function " << std::chrono::duration_cast<Duration>(en - st).count() / 100000 << "ns each" << std::endl;
        
        std::cout << std::endl;
    }
}
