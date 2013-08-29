#include <vector>
#include <functional>
#include <iostream>


template<typename Signature> struct Function;
template<typename R, typename A> struct fptr_t { typedef R(*type)(A); };
template<typename R> struct fptr_t<R, void> { typedef R(*type)(); };


template<typename R, typename A>
struct Function<R(A)>
{       
    typedef typename fptr_t<R, A>::type fptr_t;    
    template<typename F> Function(F f) : fptr(f) { }
    template<typename F> void operator=(F f) { fptr = f; }
    R operator()(A a) const { return this->fptr(a); }    
    fptr_t fptr;
};

template<typename A>
struct Function<void(A)>
{       
    typedef typename fptr_t<void, A>::type fptr_t;  
    Function() : fptr([](A&){}) { }  
    template<typename F> Function(F f) : fptr(f) { }
    template<typename F> void operator=(F f) { fptr = f; }
    void operator()(A a) const { this->fptr(a); }
    fptr_t fptr;
};

template<>
struct Function<void()>
{       
    typedef typename fptr_t<void, void>::type fptr_t;    
    Function() : fptr([]{}) { }
    template<typename F> Function(F f) : fptr(f) { }
    template<typename F> void operator=(F f) { fptr = f; }
    void operator()() const { this->fptr(); }
    fptr_t fptr;
};


enum {
    FIN = (1 << 0),
    SYN = (1 << 1),
    ACK = (1 << 2),
    RST = (1 << 3)
};

void test()
{
    auto error_func = []{ printf("invalid combination of flags"); };
    std::vector<Function<void()>> functions(uint8_t(-1), error_func);
    
    functions[0] = []{ printf("no flags"); };
    functions[SYN] = []{ printf("SYN"); };
    functions[FIN] = []{ printf("FIN"); };
    functions[ACK] = []{ printf("ACK"); };    
    functions[SYN|ACK] = []{ printf("SYN|ACK"); };
    functions[FIN|ACK] = []{ printf("FIN|ACK"); };
    functions[RST] = []{ printf("RST"); };
    
    unsigned index = 0;
    for (auto&& f : functions)
    {
        printf("\n%u\t", index++);
        f();
    }
}

int main()
{    
    test();    
}