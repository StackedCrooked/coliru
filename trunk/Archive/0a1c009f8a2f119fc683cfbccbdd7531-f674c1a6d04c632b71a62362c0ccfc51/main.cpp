#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

template<typename T>
struct Maybe
{
    Maybe(std::exception_ptr ptr) : ptr_(ptr), obj_() {}
    Maybe(T&& t) : ptr_(), obj_(std::forward<T>(t)) {}
    
    T get() const
    {
        if (ptr_)
        {
            rethrow();
        }
        return std::move(obj_);
    }
    
    explicit operator bool() const { return !ptr_; }
    
    const char* what() const
    {
        assert(ptr_);
        try
        {
            rethrow();
        }
        catch (const std::exception& exc)
        {
            return exc.what();
        }
        return "...";
    }
    
    void rethrow() const
    {
        std::rethrow_exception(ptr_);
    }
    
    std::exception_ptr ptr_;
    T obj_;
};



std::string load_resource(std::string id)
{
    if (id == "bad") throw std::runtime_error("failed to load: " + id);
    
    return "[resource:" + id + "]";
}



template<typename F, typename ...Args>
auto Try(F && f, Args&& ...args) -> Maybe<decltype(f(std::forward<Args>(args)...))>
{
    try
    {
        return Maybe<decltype(f(std::forward<Args>(args)...))>(f(std::forward<Args>(args)...));
    }
    catch (...)
    {
        return Maybe<decltype(f(std::forward<Args>(args)...))>(std::current_exception());
    }
}



int main()
{
    auto result = Try(load_resource, "something");
    std::cout << "result: " << (result ? result.get() : result.what()) << std::endl;
}


