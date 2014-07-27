#include <future>
#include <string>


template<typename T>
auto make_ready_future(T&& t) -> std::future<T>
{
    std::promise<T> prom;
    std::future<T> fut = prom.get_future();
    prom.set_value(std::forward<T>(t));
    return fut;
}


// for making a future<void>
inline auto make_ready_future() -> std::future<void>
{
    std::promise<void> prom;
    std::future<void> fut = prom.get_future();
    prom.set_value();
    return fut;
}


const std::string& get_name()
{
    static std::string name = "John";
    return name;
}


std::string get_name(const std::string& prefix)
{
    return prefix + " " + get_name();
}

int main()
{
    auto a = make_ready_future(get_name()); // ok
    auto b = make_ready_future(get_name("Sir")); // ok
    
    
    std::future<std::string> c = make_ready_future(get_name("Sir")); // ok
    
    std::future<std::string> d = make_ready_future(get_name()); // error: return type mismatch from std::future<std::string&>

    std::future<std::string> d = make_ready_future<std::string>(get_name()); // error: no matching overload
}