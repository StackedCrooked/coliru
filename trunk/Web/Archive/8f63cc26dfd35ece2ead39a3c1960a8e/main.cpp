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


typedef boost::variant<Zip, Plain> CompressionVariant;


template<typename R, typename VisitorType, typename A>
R visit(VisitorType & var, const A & a)
{
    Visitor<R, A> visitor(a);
    var.apply_visitor(const_cast<Visitor<R, A>&>(visitor));
    return visitor.r;
}


int main()
{
    std::vector<CompressionVariant>  compressors = { Zip{}, Plain{} };
    
    std::string s = "test";    
    std::cout << visit<std::string>(compressors.at(0), s) << std::endl;
    std::cout << visit<std::string>(compressors.at(1), s) << std::endl;
}