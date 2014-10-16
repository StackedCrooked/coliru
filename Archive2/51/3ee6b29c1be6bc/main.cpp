#include <future>
#include <iostream>
#include <stdexcept>


struct ReadyException
{
    ReadyException(std::exception_ptr ptr) : mExceptionPtr(ptr) {}

    template<typename T>
    operator std::future<T>() const
    {
        std::promise<T> p;
        p.set_exception(mExceptionPtr);
        return p.get_future();
    }

    std::exception_ptr mExceptionPtr;
};


inline ReadyException MakeReadyException()
{
    return ReadyException(std::current_exception());
}


inline ReadyException MakeReadyException(std::exception_ptr ptr)
{
    return ReadyException(ptr);
}


template<typename E>
inline ReadyException MakeReadyException(E e) 
{
    return ReadyException(std::make_exception_ptr(e));
}


int main()
{
    std::future<int&> fut = []() -> std::future<int&>
    {
        try { throw std::runtime_error("Test"); }
        catch (...) { return MakeReadyException(); }
    }();
    
    try { std::cout << "Got " << fut.get() << '\n'; }
    catch (...) { std::cout << "Caught exception.\n"; }
}
