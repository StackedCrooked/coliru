#ifndef CONTINUATION_H
#define CONTINUATION_H

#include <future>


namespace detail {

template<typename F, typename W, typename R>
struct helper
{
    F f;
    W w;

    helper(F f, W w)
        : f(std::move(f))
        , w(std::move(w))
    {
    }

    helper(const helper& other)
        : f(other.f)
        , w(other.w)
    {
    }

    helper(helper&& other)
        : f(std::move(other.f))
        , w(std::move(other.w))
    {
    }

    helper& operator=(helper other)
    {
        f = std::move(other.f);
        w = std::move(other.w);
        return *this;
    }

    R operator()()
    {
        f.wait();
        return w(std::move(f));
    }
};

}

namespace util
{
    template<typename F, typename W>
    auto then(F f, W w) -> std::future<decltype(w(std::move(f)))>
    {
        return std::async(std::launch::async, detail::helper<F, W, decltype(w(std::move(f)))>(std::move(f), std::move(w)));
    }
}

#endif



int main()
{
    std::promise<int> prom;
    auto fut = prom.get_future();
    printf("starting\n");
    
    std::thread th([&](){
        printf("setting promised value\n");
    	prom.set_value(42);
    });

    util::then(std::move(fut), [](std::future<int> f){
        printf("future got: %i\n", f.get());
    });
    
    printf("joining\n");
    th.join();

    printf("done\n");
}