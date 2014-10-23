#include <boost/any.hpp>
#include <functional>
#include <map>
#include <cstddef>
#include <memory>
#include <tuple>
#include <utility>
#include <iostream>
#include <string>

struct IGenericFunction
{
    virtual ~IGenericFunction() = default;
    
    virtual void call(boost::any a1 = boost::any{}
                    , boost::any a2 = boost::any{}
                    , boost::any a3 = boost::any{}
                    , boost::any a4 = boost::any{}) = 0;
};

template <typename... Args>
class GenericFunction : public IGenericFunction
{
public:
    GenericFunction(std::function<void(Args...)> f) : _f{ f } {}
    
    virtual void call(boost::any a1 = boost::any{}
                    , boost::any a2 = boost::any{}
                    , boost::any a3 = boost::any{}
                    , boost::any a4 = boost::any{}) override
    {
        call_func(std::make_tuple(a1, a2, a3, a4)
                , std::make_index_sequence<sizeof...(Args)>{});
    }

private:          
    template <typename Tuple, std::size_t... Indices>
    void call_func(Tuple t, std::index_sequence<Indices...> s)
    {
        _f(boost::any_cast<
               typename std::tuple_element<Indices, Params>::type
           >(std::get<Indices>(t))...);
    }
    
    std::function<void(Args...)> _f;
    
    using Params = std::tuple<Args...>;
};

template <typename... Args>
std::shared_ptr<IGenericFunction> make_generic_function_ptr(void(*f)(Args...))
{
    return std::make_shared<GenericFunction<Args...>>(f);
}

void foo(int x)
{
    std::cout << x;    
}

void bar()
{
    std::cout << "bar";
}

int main()
{
    std::map<std::string, std::shared_ptr<IGenericFunction>> map
    {
        {"foo", make_generic_function_ptr(&foo)},
        {"bar", make_generic_function_ptr(&bar)}
    };
    
    map["foo"]->call(2);
    
    std::cout << std::endl;
    
    map["bar"]->call();
}
