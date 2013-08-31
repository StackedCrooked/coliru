#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <tuple>

struct Zip {    
    std::string operator()(const std::string &s) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return s;
    }
};

struct Plain {    
    std::string operator()(const std::string &s) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return s;
    }
};

typedef boost::variant<Zip, Plain> Compressor;

template<typename ...Args>
class generic_visitor : public boost::static_visitor<>
{   
public:
    template<typename ...A>
    generic_visitor(A && ...args) : args_{std::forward<A>(args)...}
    {
    }

    template<typename C>
    void operator()(C & c)
    {
        call(c, typename gens<sizeof...(Args)>::type());
    }
    
private:
    template<int ...> struct seq { };
    template<int N, int ...S> struct gens : gens<N-1, N-1, S...> { };
    template<int ...S> struct gens<0, S...> { typedef seq<S...> type; }; 
    
    template<typename C, int...S>
    void call(const C & c, seq<S...>)
    {
        c(std::get<S>(args_)...);
    }

    std::tuple<Args...> args_;
};

template<typename ...Args>
auto make_visitor(Args && ...args) -> generic_visitor<Args...>
{
    return generic_visitor<Args...>(std::forward<Args>(args)...);
}

int main()
{
    Compressor comp(Zip{});
    std::string s = "test";
    auto visitor = make_visitor(s);
    comp.apply_visitor(visitor);
}