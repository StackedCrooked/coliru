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

int main()
{   
    Server server;
    
    server.registerCommand<CreatePort>([](InterfaceId, PortOwner) -> PortId {
        return PortId();
    });    
            
    server.registerCommand<DestroyPort>([](PortId) -> bool {
        return true;
    });
}






