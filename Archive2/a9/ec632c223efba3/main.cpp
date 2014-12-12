#include <iostream>
#include <future>
#include <stdexcept>


// for making a future<void> that rethrows an exception
template<typename T, typename Exception>
inline auto MakeExceptionalFuture(Exception e) -> std::future<T>
{
    std::cout << "MakeExceptionalFuture(Exception e)" << std::endl;
    std::promise<T> prom;
    try { throw e; } catch (...) { prom.set_exception(std::current_exception()); }
    return prom.get_future();
}


// for making a future<void> that rethrows an exception
template<typename T, typename Exception>
inline auto MakeExceptionalFuture(std::exception_ptr eptr) -> std::future<T>
{
    std::cout << "MakeExceptionalFuture(std::exception_ptr eptr)" << std::endl;
    std::promise<T> prom;
    prom.set_exception(eptr);
    return prom.get_future();
}


int main()
{
    try
    {
        throw std::runtime_error("Test");
    } 
    catch (...)
    {
        std::future<int> f = MakeExceptionalFuture<int>(std::current_exception());
        f.get();
    }
}
