#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <tuple>
#include <utility>
#include <string>
#include <boost/any.hpp>

template<typename... Args>
struct dispatcher
{
    template<typename F>
    dispatcher(F f) : _f(std::move(f)) { }

    void operator () (std::vector<boost::any> const& v)
    {
        if (v.size() < sizeof...(Args))
        {
            std::cout << "Bad arity!" << std::endl; // Throw if you prefer
            return;
        }

        return do_call(v, std::make_integer_sequence<int, sizeof...(Args)>());
    }

private:
    template<int... Is>
    void do_call(std::vector<boost::any> const& v, std::integer_sequence<int, Is...>)
    {
        try
        {
            return _f((get_ith<Args>(v, Is))...);
        }
        catch (boost::bad_any_cast const&)
        {
            std::cout << "Bad argument!" << std::endl; // Throw if you prefer
        }
    }

    template<typename T>
    T get_ith(std::vector<boost::any> const& v, int i)
    {
        return boost::any_cast<T>(v[i]);
    }
    
private:
    std::function<void(Args...)> _f;
};

typedef std::function<void(std::vector<boost::any> const&)> dispatcher_type;

template<typename T>
struct function_traits;

template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...)>
{
    using args_type = std::tuple<Args...>;
};

template<typename R, typename C, typename... Args>
struct function_traits<R(C::*)(Args...) const>
{
    using args_type = std::tuple<Args...>;
};

template<typename T>
struct dispatcher_maker;

template<typename... Args>
struct dispatcher_maker<std::tuple<Args...>>
{
    template<typename F>
    dispatcher_type make(F&& f)
    {
        return dispatcher<Args...>{std::forward<F>(f)};
    }
};

template<typename F>
std::function<void(std::vector<boost::any> const&)> make_dispatcher(F&& f)
{
    using f_type = decltype(&F::operator());
    
    using args_type = typename function_traits<f_type>::args_type;
    
    return dispatcher_maker<args_type>{}.make(std::forward<F>(f)); 
}

template<typename... Args>
std::function<void(std::vector<boost::any> const&)> make_dispatcher(void(*f)(Args...))
{
    return dispatcher_maker<std::tuple<Args...>>{}.make(f);
}

struct event_dispatcher
{
public:
    template<typename F>
    void listen(std::string const& event, F&& f)
    {
        _callbacks.emplace(event, make_dispatcher(std::forward<F>(f)));
    }
    
    template<typename... Args>
    void fire(std::string const& event, Args const&... args)
    {
        auto rng = _callbacks.equal_range(event);
        for (auto it = rng.first; it != rng.second; ++it)
        {
            call(it->second, args...);
        }
    }
    
private:
    template<typename F, typename... Args>
    void call(F const& f, Args const&... args)
    {
        std::vector<boost::any> v{args...};
        f(v);
    }

private:
    std::multimap<std::string, dispatcher_type> _callbacks;
};

void my_handler(int x, const char* c, double d)
{
    std::cout << "Got a " << x << " and a " << c << " as well as a " << d << std::endl;    
}

int main()
{
    event_dispatcher events;
    
    events.listen("key", 
                  [] (int x) 
                  { std::cout << "Got a " << x << std::endl; });
    
    events.listen("key", 
                  [] (int x, std::string const& s) 
                  { std::cout << "Got a " << x << " and a " << s << std::endl; });
    
    events.listen("key", 
                  [] (int x, std::string const& s, double d) 
                  { std::cout << "Got a " << x << " and a " << s << " as well as a " << d << std::endl; });

    events.listen("key", 
                  [] (int x, double d) 
                  { std::cout << "Got a " << x << " and a " << d << std::endl; });
    
    events.listen("key", my_handler);
    
    std::cout << "First firing:" << std::endl;
    
    events.fire("key", 42, std::string{"hi"});
    
    std::cout << "Second firing:" << std::endl;
    
    events.fire("key", 42, std::string{"hi"}, 3.14);
}
