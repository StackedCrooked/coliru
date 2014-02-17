#include <iostream>
#include <functional>
#include <future>

template <typename Func, typename Ret>
auto continue_with(std::future<Ret> &&fu, Func func)
    -> std::future<decltype(func(fu.get()))>
{
    struct {
        std::future<Ret> fu;
        Func func;
        
        auto operator()()
        -> decltype(func(fu.get()))
        { return func(fu.get()); }
    } fobj{std::move(fu), func};
    
    return std::async(std::move(fobj));
}


int main()
{
    /*std::future<void> fu = std::async([]{ std::cout << "fu" << std::endl; });
    std::future<void> fu2 = continue_with(
        std::move(fu),
        []{ std::cout << "fu2" << std::endl; }
        );
    fu2.get();
    std::cout << "fu continue complete" << std::endl;*/

    std::future<int> retfu = std::async([]{ std::cout << "retfu" << std::endl; return 3; });
    std::future<int> retfu2 = continue_with(
        std::move(retfu),
        [](int result){ std::cout << "retfu2 " << result << std::endl; return result + 1; }
        );
    int ret = retfu2.get();
    std::cout << "retfu continue complete : " << ret << std::endl; 

    std::cin.get();
}
