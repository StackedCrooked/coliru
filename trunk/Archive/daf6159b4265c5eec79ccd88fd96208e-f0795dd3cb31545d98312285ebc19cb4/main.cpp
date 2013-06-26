#include <stdexcept>
#include <string>
#include <memory>
#include <boost/variant.hpp>
#include <stdio.h>


template<typename T>
struct Maybe
{
    Maybe(std::exception_ptr ptr) : result(ptr) {}
    
    Maybe(T&& t) : result(std::move(t)) {}
    
    const T& peek() const
    {
        if (auto exc_ptr = boost::get<std::exception_ptr>(&result))
        {
            std::rethrow_exception(*exc_ptr);
        }
        return boost::get<T>(result);
    }
    
    T pop()
    {
        if (auto exc_ptr = boost::get<std::exception_ptr>(&result))
        {
            std::rethrow_exception(*exc_ptr);
        }
        return std::move(boost::get<T>(result));
    }
    
    
    explicit operator bool() const noexcept { return boost::get<T>(&result); }
    
    const char* what() const noexcept
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
        std::rethrow_exception(boost::get<std::exception_ptr>(result));
    }
    
    boost::variant<T, std::exception_ptr> result;
};



std::string load_resource(std::string id)
{
    if (id != "a") throw std::runtime_error("bad id: " + id);
    
    return "resource(" + id + ")";
}



template<typename F, typename ...Args>
auto Try(F && f, Args&& ...args) noexcept -> Maybe<decltype(f(std::forward<Args>(args)...))>
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


void test(const std::string& name) noexcept
{
    auto result = Try(load_resource, name);
    if (result)
    {
        puts(result.pop().c_str());
    }
    else
    {
        puts(result.what());
    }
}


int main()
{
    test("a");
    test("b");
    test("c");
}


