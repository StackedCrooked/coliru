#include "boost/variant.hpp"
#include <iostream>
#include <string>


struct Plain { void compress(std::string & ) {} };
struct Zip   { void compress(std::string & s) { s += "_zipped"; } };


struct visitor : boost::static_visitor<>
{
    visitor(std::string & s) : sp(&s) {}
    
    template<typename C>
    void operator()(C & c) const
    {
        c.compress(*sp);
    }
    
    std::string * sp;
};


int main()
{
    {
        boost::variant<Zip, Plain> var{Plain{}};
        std::string s = "text";
        visitor vis(s);
        var.apply_visitor(vis);    
        std::cout << s;
    }
    {
        boost::variant<Zip, Plain> var{Zip{}};
        std::string s = "text";
        visitor vis(s);
        var.apply_visitor(vis);    
        std::cout << s;
    }
}

