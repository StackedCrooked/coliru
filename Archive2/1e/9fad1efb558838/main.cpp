#include <utility>
#include <vector>
#include <functional>
#include <iostream>

#include <boost/any.hpp>

namespace ns {

using any = boost::any;
using arg_type = std::vector<any>;

struct bad_signature: std::exception {};
struct bad_arity: bad_signature {};
struct bad_argument: bad_signature {
    explicit bad_argument(int which): which{which} {}
    int which;
};

template<typename Callable, typename Indices, typename... Args>
struct erased_callback;

template<typename Callable, std::size_t... Indices, typename... Args>
struct erased_callback<Callable, std::index_sequence<Indices...>, Args...> {
    // you can provide more overloads for cv/ref quals
    void operator()(arg_type args)
    {
        // you can choose to be lax by using <
        if(args.size() != sizeof...(Args)) {
            throw bad_arity {};
        }

        callable(restore<Args>(args[Indices], Indices)...);
    }

    Callable callable;

private:
    template<typename Arg>
    static Arg&& restore(any& arg, int index)
    {
        using stored_type = std::decay_t<Arg>;
        if(auto p = boost::any_cast<stored_type>(&arg)) {
            return std::forward<Arg>(*p);
        } else {
            throw bad_argument { index };
        }
    }
};

template<
    typename... Args, typename Callable
    , typename I = std::make_index_sequence<1>
>
erased_callback<std::decay_t<Callable>, I, Args...> erase(Callable&& callable)
{ return { std::forward<Callable>(callable) }; }

// in turn we can erase an erased_callback:
using callback_type = std::function<void(arg_type)>;

} // ns

int main()
{
    auto f = [](int i) { std::cout << "I got a(n) " << i << '\n'; };
    auto g = ns::erase<int>(std::move(f));
    
    g({ 18 });
    
    try {
        g({ "lol" });
    } catch(ns::bad_argument const& ex) {
        std::cout << "Something went wrong at:\t" << ex.which << '\n';
    }
    
    try {
        g({ 8, 19 });
    } catch(ns::bad_arity const&) {
        std::cout << "Bad arity!\n";
    }
}