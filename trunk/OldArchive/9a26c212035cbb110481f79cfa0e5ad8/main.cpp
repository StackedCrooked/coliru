#include "boost/variant.hpp"
#include <iostream>
#include <string>
#include <tuple>


namespace policies {

template<typename ...Args>
class Arguments {
    template<int ...> struct seq { };
    template<int N, int ...S> struct gens : gens<N-1, N-1, S...> { };
    template<int ...S> struct gens<0, S...> { typedef seq<S...> type; };    
    template<typename F, int...S> void do_apply_on(const F & f, seq<S...>) { f(std::get<S>(args_)...); }
    mutable std::tuple<Args...> args_;
    
public:
    template<typename ...A> Arguments(A && ...args) : args_{std::forward<A>(args)...} {}

    template<typename F> void apply_on(const F & f) const
    {
        do_apply_on(f, typename gens<sizeof...(Args)>::type());
    }
};

template<class T> struct PolicyInterface
{
    template<typename ...Args>
    void operator()(Args && ...args) const
    {
        static_cast<const T&>(*this).invoke(std::forward<Args>(args)...);
    }
};


template<typename ...Args>
struct PolicyVisitor : Arguments<Args...>, boost::static_visitor<>
{
    template<typename ...A>
    PolicyVisitor(A && ...args) : Arguments<Args...>(std::forward<Args>(args)...) {}

    template<typename C>
    void operator()(const PolicyInterface<C> & c) const
    {
        this->apply_on(c);
    }
};


template<typename ...Args>
PolicyVisitor<Args...> MakePolicyVisitor(Args && ...args)
{
    return PolicyVisitor<Args...>(std::forward<Args>(args)...);
}


template<typename P, typename ...Args>
void RunPolicy(const P & p, Args && ...args)
{
    auto v = MakePolicyVisitor(std::forward<Args>(args)...);
    p.apply_visitor(v);
}


} // namespace policies


namespace policies {
namespace compression {


struct Plain : PolicyInterface<Plain>
{
    void invoke(std::ostream & os, const std::string & s) const
    {
        os << "plain[" << s << "]";
    }
};


struct Zip : PolicyInterface<Zip>
{
    void invoke(std::ostream & os, const std::string & s) const
    {
        os << "zip[" << s << "]";
    }
};


typedef boost::variant<Plain, Zip> Policy;


} } // namespace policies::compression


class Archive
{
    typedef policies::compression::Policy CompressionPolicy;
    mutable CompressionPolicy comp;
    
public:
    Archive(const CompressionPolicy & c) : comp(c)
    {
    }
    
    void archive(std::ostream & os, const std::string & s)
    {
        RunPolicy(comp, os, s);
    }    
};


int main()
{
    using policies::compression::Zip;
    using policies::compression::Plain;
    
    Archive zip_archive(Zip{});
    zip_archive.archive(std::cout, "ziptest");
    
    std::cout << std::endl;
    
    Archive plain_archive(Plain{});
    plain_archive.archive(std::cout, "plaintest");
}

