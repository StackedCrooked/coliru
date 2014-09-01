#include <vector>
#include <string>
#include <exception>
#include <utility>
#include <tuple>
#include <cstdlib>\
#include <iostream>

struct foo{};

// this function can throw std::exception, std::string, int or unhandled
void function(int, foo, int) 
{
  std::vector<int> x{1,2,3,4,5};
  auto val = x.at(x.size()); //throw out-of-range error
}

template<typename Func, typename... Args>
struct exception_wrapper
{
    exception_wrapper(Func f, Args... args) 
    : f_(std::move(f))
    , args_(std::make_tuple(std::move(args)...))
    {}
    
    ~exception_wrapper() 
    {
        try {
            invoke();
        } catch(std::exception const& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        } catch(...) {
            std::cerr << "Caught unknown exception" << std::endl;
        }
    }
    
    template<std::size_t... I>
    void apply(std::index_sequence<I...>)
    {
        f_(std::get<I>(args_)...);
    }
    
    void invoke()
    {
        return apply(std::make_index_sequence<sizeof...(Args)>());
    }
    
    Func f_;
    std::tuple<Args...> args_;
};

template<typename Func, typename... Args>
auto make_exception_wrapper(Func&& f, Args&&... args)
{
    return exception_wrapper<Func, Args...>(
        std::forward<Func>(f), std::forward<Args>(args)...);
}

int main()
{
    make_exception_wrapper(function, 10, foo{}, 20);
}
