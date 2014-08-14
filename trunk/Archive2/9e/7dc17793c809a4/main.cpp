#include <pthread.h>

#include <iostream>
#include <tuple>


template<int...> struct int_seq {};
template<int N, int... I> struct make_int_seq : make_int_seq<N-1, N-1, I...> {};
template<int... I> struct make_int_seq<0, I...> : int_seq<I...> {};


template<typename F, typename... Args>
struct thread_arg_pack
{
    F fun;
    std::tuple<Args...> args;
    
    static void* thread_fun(void* rp)
    {
        auto p = static_cast<thread_arg_pack*>(rp);
        p->run();
        delete p;
        
        return nullptr;
    }
    
    using thread_fun_t = void* (*)(void*);
    thread_fun_t get_thread_fun() const noexcept
    { return thread_fun; }
    
    void run() { run(make_int_seq<sizeof...(Args)>{}); }
    
    template<int... I>
    void run(int_seq<I...>)
    {
        fun( std::get<I>(args)... );
    }
};


class thread
{
    pthread_t _tid;

public:
    thread() :
    _tid(0)
    { }

    template <typename F, typename... Args>
    thread(F f, Args... args)
    {
        auto p = new thread_arg_pack<F, Args...>{f, std::make_tuple(args...)};
        pthread_create(&_tid, 0, p->get_thread_fun(), p);
    }
    
    void join()
    {
        pthread_join(_tid, nullptr);
    }
};

/** USAGE **/
void
test(int i, char c)
{
    std::cout << "test: ";
    while (i > 0) {
        std::cout << c;
        i--;
    }
    std::cout << std::endl;
}

int main(const int argc, const char** argv)
{
    thread t(test, 6, 'a');
    t.join();
}