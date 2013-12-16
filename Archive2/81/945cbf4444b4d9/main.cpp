#include <iostream>
#include <type_traits>
#include <new>
#include <utility>


struct Functor // only supports signature `void()`
{
    template<typename F>
    Functor(F&& f)
    {        
        static_assert(sizeof(f) <= sizeof(buf), "");
        static_assert(std::alignment_of<F>::value <= std::alignment_of<SmallBuffer>::value, "");
        new (&buf) F(std::forward<F>(f));
        
        fptr = &Functor::call<F>;
    }
    
    Functor(Functor&& rhs) : buf(rhs.buf), fptr(rhs.fptr)
    {
        rhs.fptr = nullptr;
    }
    
    Functor& operator=(Functor&& rhs)
    {
        buf = rhs.buf;
        fptr = rhs.fptr;
        rhs.fptr = nullptr;
        return *this;
    }
    
    Functor(const Functor&) = delete;
    Functor& operator=(const Functor&) = delete;
    
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
    Functor([&]{ std::cout << ++a << std::endl; })();
}

