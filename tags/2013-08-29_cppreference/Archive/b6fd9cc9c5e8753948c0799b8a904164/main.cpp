#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>


struct Zip
{    
    std::string operator()(const std::string &s) const
    {
        return "zipped: " + s;
    }
};

struct Plain
{    
    std::string operator()(const std::string &s) const
    {
        return "plain: " + s;
    }
};

template<typename R, typename A>
struct Visitor : boost::static_visitor<>
{
    
    Visitor(const A & a) : a(a) {}
    
    template<typename F>
    void operator()(const F & f)
    {
        r = f(a);
    }
    
    A a;
    R r;
};


template<typename R, typename VisitorType, typename A>
R apply(VisitorType & var, A && a)
{
    Visitor<R, A> visitor(a);
    var.apply_visitor(visitor);
    return visitor.r;
}


int main()
{
    boost::variant<Zip, Plain> strategy{Zip{}};    
    std::cout << apply<std::string>(strategy, "test") << std::endl;
}