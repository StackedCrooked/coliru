#include "boost/variant.hpp"
#include <iostream>
#include <string>


struct Plain
{
    void compress(std::ostream & os, const std::string & s)
    {
        os << s;
    }
};


struct WithStars
{
    void compress(std::ostream & os, const std::string & s)
    {
        os << "*** " << s << " ***";
    }
};


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
    typedef boost::variant<WithStars, Plain> Compressor;
    
    template<typename C>
    Archive(const C & c) : mCompressor{c} { }
    
    void archive(std::ostream & os, const std::string & s) const
    {   
        visitor v{os, s};
        mCompressor.apply_visitor(v);
    }
    
    mutable Compressor mCompressor;
};


int main()
{
    Archive arch{WithStars{}};
    arch.archive(std::cout, "some text\");
    std::cout << std::endl;
    
    Archive arch2{Plain{}};
    arch2.archive(std::cout, "some text");
}

