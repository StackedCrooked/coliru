#include <tuple>
#include <functional>
#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace Detail {
    

template<int ...>
struct Sequence
{
};


template<int N, int ...S>
struct GenerateSequence : GenerateSequence<N - 1, N - 1, S...>
{
};


template<int ...S>
struct GenerateSequence<0, S...>
{
    typedef Sequence<S...> type;
};


template<typename F, typename Tuple, int ...Indices>
auto do_explode(F f, const Tuple& tuple, Sequence<Indices...>) -> decltype(f(std::get<Indices>(tuple)...))
{
    return f(std::get<Indices>(tuple)...);
}


} // namespace Detail


template<typename F, typename ...T>
auto explode(F&& f, const std::tuple<T...>& tup) -> decltype(do_explode(f, tup, std::declval<typename Detail::GenerateSequence<sizeof...(T)>::type>()))
{
    using Sequence = typename Detail::GenerateSequence<sizeof...(T)>::type;
    return Detail::do_explode(std::forward<F>(f), tup, Sequence{});
}


int sum(int a, int b, int c)
{
    return a + b + c;
}

#define TRACE std::cout << __PRETTY_FUNCTION__  << std::endl;


struct Server
{    
    template<typename Command, typename Function>
    void registerCommand(const Function & f)
    {
        TRACE
        typedef typename Command::argument_type arg_tuple;
        explode(f, arg_tuple());
    }


};



struct PortId {};
struct InterfaceId {};
struct PortOwner {};

struct CreatePort
{   
    typedef std::tuple<InterfaceId, PortOwner> argument_type;
    typedef PortId result_type;
};


struct DestroyPort
{   
    typedef std::tuple<PortId> argument_type;
    typedef bool result_type;
};

template<typename Command>
void print_signature(std::function<typename Command::result_type(typename Command::argument_type)>  = std::function<typename Command::result_type(typename Command::argument_type)>())
{
    TRACE
}

int main()
{       
    auto tup = std::make_tuple(1, 2, 3);
    std::cout << explode(sum, tup) << std::endl;
    
    print_signature<CreatePort>();
    
    Server server;
    server.registerCommand<CreatePort>([](InterfaceId, PortOwner) -> PortId {
        TRACE
        return PortId();
    });
    
    server.registerCommand<DestroyPort>([](PortId) -> bool {
        TRACE
        return true;
    });
}
