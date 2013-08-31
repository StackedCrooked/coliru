#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <boost/variant.hpp>


template<typename T>
struct Maybe
{
    explicit Maybe(std::exception_ptr ptr) : result(ptr) {}
    
    explicit Maybe(T&& t) : result(std::move(t)) {}
    
    explicit operator bool() const { return boost::get<T>(&result); }
    
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
        std::rethrow_exception(boost::get<std::exception_ptr>(result));
    }
    
    boost::variant<T, std::exception_ptr> result;
};


template<typename F, typename ...Args>
auto attempt(F && f, Args&& ...args) -> Maybe<decltype(f(std::forward<Args>(args)...))>
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


//
// test
//
std::string load_resource(std::string id)
{
    if (id != "a") throw std::runtime_error("bad id: " + id);    
    return "resource(" + id + ")";
}


void test(const std::string& name)
{
    auto result = attempt(load_resource, name);
    if (result)
    {
        std::cout << "Success: " << result.pop() << std::endl;
    }
    else
    {
        std::cout << "Failure: " << result.what() << std::endl;
    }
}


int main()
{
    test("a");
    test("aa");
}
