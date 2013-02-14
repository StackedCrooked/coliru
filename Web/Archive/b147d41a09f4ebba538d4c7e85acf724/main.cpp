#include <functional>
#include <future>
#include <iostream>


// Lazy<T> holds the result of a deferred (synchronous and non-threaded)operation.
template<typename T>
struct Lazy : std::future<T>
{
    // Workaround for lack of inherited constructors.
    template<typename ...Args>
    Lazy(Args && ...args) : std::future<T>(std::forward<Args>(args)...) {}
};

// Implement Lazy<T&> in terms of Lazy< std::reference_wrapper<T> >.
template<typename T>
struct Lazy<T&> : Lazy< std::reference_wrapper<T> >
{
    template<typename ...Args>
    Lazy(Args && ...args) : Lazy< std::reference_wrapper<T> >(std::forward<Args>(args)...) {}    
};


// Defers calling a function and returns a lazy result.
template<typename F>
inline auto Defer(F f) -> decltype(std::async(std::launch::deferred, f))
{
    return std::async(std::launch::deferred, f);
}


int main()
{
    {
        int a = 2, b = 3;    
        Lazy<int> lazy = Defer([=]() { return a + b; });
        std::cout << lazy.get() << std::endl;        
    }
    
    {
        Lazy<int&> lazy_ref = Defer([]() { static int n = 1; return std::ref(n); }); // adding std::ref should probably not be user's job
        int & n = lazy_ref.get();
        std::cout << n << std::endl;   
    }    
    
}