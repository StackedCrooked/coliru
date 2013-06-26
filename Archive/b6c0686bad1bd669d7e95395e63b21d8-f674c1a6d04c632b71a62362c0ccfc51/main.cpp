#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>


template<typename T>
struct Maybe
{
    Maybe(std::exception_ptr ptr) : ptr_(ptr), obj_() {}
    
    Maybe(T&& t) : ptr_(), obj_(std::unique_ptr<T>(new T(std::move(t)))) {}
    
    T get()
    {
        if (ptr_)
        {
            rethrow();
        }
        T result = std::move(*obj_);
        obj_.reset();
        return std::move(result);
    }
    
    explicit operator bool() const { return !ptr_; }
    
    const char* what() const
    {
        try
        {
            rethrow();
        }
        catch (const std::exception& exc)
        {
            return exc.what();
        }
        catch (...)
        {
            return "...";
        }
        return "";
    }
    
private:
    void rethrow() const
    {
        std::rethrow_exception(ptr_);
    }
    
    std::exception_ptr ptr_;
    std::unique_ptr<T> obj_; // use std::optional if available
};



std::string load_resource(std::string id)
{
    if (id != "a") throw std::runtime_error("bad id: " + id);
    
    return "resource(" + id + ")";
}



template<typename F, typename ...Args>
auto Try(F && f, Args&& ...args) -> Maybe<decltype(f(std::forward<Args>(args)...))>
{
    try
    {
        return Maybe<decltype(f(std::forward<Args>(args)...))>(std::move(f(std::forward<Args>(args)...)));
    }
    catch (...)
    {
        return Maybe<decltype(f(std::forward<Args>(args)...))>(std::current_exception());
    }
}


void test(const std::string& name)
{
    auto result = Try(load_resource, name);
    if (result)
    {
        std::cout << result.get() << std::endl;
    }
    else
    {
        std::cout << result.what() << std::endl;
    }
}


int main()
{
    test("a");
    test("b");
    test("c");
}


