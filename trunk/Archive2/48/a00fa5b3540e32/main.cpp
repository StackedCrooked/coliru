#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <utility>
#include <future> 
#include <atomic>
#include <chrono>
#include <type_traits> 

/*
template<class Fn, class ...Args>
auto my_async(Fn f, Args&&... args) -> std::future<std::result_of_t<Fn(Args...)>>
{
    using ret_t = std::result_of_t<Fn(Args...)>;
    std::promise<ret_t> p;
    auto fut = p.get_future();
    auto wrapper = [p_ = std::move(p), f_ = std::move(f)](auto&& ... a)mutable
    { 
        p_.set_value(f_(std::move(a)...));
    };
    
    std::thread(wrapper, std::forward<Args>(args)...).detach();
    return fut;
}
*/

template<class Fn>
auto make_packaged_task(Fn f)
{
    return std::packaged_task<int()>(f);
}

template<class Fn, class ...Args>
auto my_async(Fn f, Args&&... args) -> std::future<std::result_of_t<Fn(Args...)>>
{
    auto pt = make_packaged_task(f);
    auto fut = pt.get_future();
    
    std::thread(std::move(pt), std::forward<Args>(args)...).detach();
    return fut;
}

int main()
{
    std::atomic<int> count{0};
    //int count{0};
    std::vector<std::future<int>> fv;
    auto start = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < 1000; ++i)
    {
        //fv.push_back(my_async([&]{ ++count; std::cout << count << ','; return 0; }));
        //fv.push_back(std::async(std::launch::async | std::launch::deferred, [&]{ std::cout << ++count << ','; return 0; }));
        //fv.push_back(std::async(std::launch::async, [&]{ std::cout << ++count << ','; return 0; }));
        fv.push_back(std::async(std::launch::deferred, [&]{ std::cout << ++count << ','; return 0; }));
    }
    
    for(auto&& f : fv)
    {
        f.get();
    }
    
    auto diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "\ntime: " << std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
}
