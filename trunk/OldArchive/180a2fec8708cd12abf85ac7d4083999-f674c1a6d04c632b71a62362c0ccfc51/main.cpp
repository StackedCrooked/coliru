#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>


template<typename T>
struct Maybe
{
    Maybe(std::exception_ptr ptr) : ptr_(ptr), obj_() {}
    
    Maybe(T&& t) : ptr_(), obj_(std::move(t)) {}
    
    const T& get() const
    {
        if (ptr_)
        {
            rethrow();
        }
        return obj_;
    }
    
    T steal()
    {
        return std::move(obj_);
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
    T obj_;
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
        std::cout << "Success: " << result.steal() << std::endl;
    }
    else
    {
        std::cout << "Failure: " << result.what() << std::endl;
    }
}


int main()
{
    test("a");
    test("b");
    test("c");
}


