#include <future>
#include <string>
#include <type_traits>
#include <functional>
#include <utility>

template<class T>
struct unwrap_ref{ using type = T; };

template<class T>
struct unwrap_ref<std::reference_wrapper<T>>{ using type = T&; };

template<typename T,
    typename Decayed = typename std::decay<T>::type,
    typename Result = typename unwrap_ref<Decayed>::type>
auto make_ready_future(T&& t) -> std::future<Result>
{
    std::promise<Result> prom;
    std::future<Result> fut = prom.get_future();
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
}