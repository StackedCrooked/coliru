#include <iostream>
#include <type_traits>
#include <new>
#include <utility>


struct Functor // only supports signature `void()`
{
    template<typename F>
    Functor(F&& f, typename std::enable_if<!std::is_same<typename std::remove_reference<typename std::remove_const<F>::type>::type,Functor>::value>::type* = 0)
    {        
        static_assert(sizeof(f) <= sizeof(buf), "");
        static_assert(std::alignment_of<F>::value <= std::alignment_of<SmallBuffer>::value, "");
        new (&buf) F(std::forward<F>(f));
        fptr = &Functor::call<F>;
    }
    
    void operator()()
    {
        fptr(&buf);        
    }
    
private:
    template<typename F>
    static void call(void* f)
    {
        (*static_cast<F*>(f))();
    }
    
    struct alignas(128) SmallBuffer
    {
        char data[128];
    };
    
    SmallBuffer buf;    
    typedef void(*FPTR)(void*);
    FPTR fptr;
};

int main()
{
    int a = 0;
    Functor f([&]{ std::cout << ++a << std::endl; });
    Functor g(std::move(f));
    f();
    g();
}

