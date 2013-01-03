
#include <boost/algorithm/string.hpp>
#include <boost/variant.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>


template<typename R, typename A>
struct Visitor : boost::static_visitor<>
{
    Visitor(const A & a) : a(a) {}
    
    template<typename F>
    void operator()(const F & f)
    {
        r = std::move(f(a));
    }
    
    const A & a;
    R r;
};


template<typename R, typename Variant, typename A>
R visit(Variant & var, const A & a)
{
    Visitor<R, A> visitor{a};
    var.apply_visitor(visitor);
    return visitor.r;
}


struct Void {}; // for Void return type


//
// Example
//
struct uppercase
{    
    std::string operator()(std::string s) const
    {
        boost::to_upper(s);
        return s;
    }
};


struct lowercase
{    
    std::string operator()(std::string s) const
    {
        boost::to_lower(s);
        return s;
    }
};


struct decorate_with_stars
{
    std::string operator()(std::string s) const
    {
        return "*** " + s + " ***";
    }
};


struct decorate_not
{
    const std::string & operator()(const std::string & s) const
    {
        return s;
    }
};


struct Formatter 
{
    template<typename Casing, typename Decoration>
    Formatter(const Casing & casing, const Decoration & dec) :
        casing(casing),
        decoration(dec)
    {
    }
    
    std::string format(const std::string & s)
    {
        return visit<std::string>(decoration, visit<std::string>(casing, s));
    }
    
    boost::variant<uppercase, lowercase> casing;
    boost::variant<decorate_with_stars, decorate_not> decoration;
};

int main()
{
    Formatter formatter(uppercase{}, decorate_with_stars{});
    std::cout << formatter.format("Hello World!") << std:endl;
}
