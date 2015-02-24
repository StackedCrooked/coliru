#include <boost/any.hpp>
#include <functional>
#include <vector>
#include <cstddef>
#include <memory>
#include <tuple>
#include <iostream>

struct IGenericFunction
{
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
        std::tuple<boost::any, boost::any, boost::any, boost::any> t{ a1, a2, a3, a4 };
        call_tuple(t, std::make_index_sequence<arity>{});
    }

private:    
    template <typename Tuple, std::size_t... Indices>
    void call_tuple(Tuple t, std::index_sequence<Indices...> s)
    {
        call_func(t, s);
    }
        
    template <typename Tuple, std::size_t... Indices>
    void call_func(Tuple t, std::index_sequence<Indices...> s)
    {
        _f(boost::any_cast<typename std::tuple_element<Indices, Params>::type>(std::get<Indices>(t))...);
    }

    static constexpr std::size_t arity = sizeof...(Args);
    
    std::function<void(Args...)> _f;
    
    using Params = std::tuple<Args...>;
};

template <typename... Args>
std::shared_ptr<IGenericFunction> make_generic_function_ptr(void(*f)(Args...))
{
    return std::make_shared<GenericFunction<Args...>>(f);
}

void func1(std::string value)
{
    std::cout << "func1 " << value << std::endl;
}

void func2(std::string value, int min, int max)
{
    std::cout << "func2 " << value << " " << min << " " << max << std::endl;
}

int main()
{
    std::vector<std::shared_ptr<IGenericFunction>> functions;
    
    functions.push_back(make_generic_function_ptr(&func1));    
    functions.push_back(make_generic_function_ptr(&func2));
    
    for (auto f : functions)
    {
        f->call(std::string("abc"), 1, 2);
    }
}