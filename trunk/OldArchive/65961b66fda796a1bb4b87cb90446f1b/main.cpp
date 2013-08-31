#include "boost/variant.hpp"
#include <iostream>
#include <string>


struct Plain { void compress(std::ostream & os, const std::string & s) { os << s << "\n";        } };
struct Zip   { void compress(std::ostream & os, const std::string & s) { os << s << "_zipped\n"; } };


struct visitor : boost::static_visitor<>
{
    visitor(std::ostream & os, std::string s) : os(os), s(s) {}
    
    template<typename C>
    void operator()(C & c) const
    {
        c.compress(os, s);
    }
    
    std::ostream & os;
    std::string s;
};


struct Archive
{
    template<typename T>
    Archive(const T & t) : var{t}
    {
    }
    
    void archive(std::ostream & os, const std::string & s)
    {   
        visitor v(os, s);
        var.apply_visitor(v);        
    }
    
    boost::variant<Zip, Plain> var;
};


int main()
{
    {
        boost::variant<Zip, Plain> var{Plain{}};
        visitor vis(std::cout, "text");
        var.apply_visitor(vis);
    }
    {
        boost::variant<Zip, Plain> var{Zip{}};
        visitor vis(std::cout, "text");
        var.apply_visitor(vis);
    }
}

